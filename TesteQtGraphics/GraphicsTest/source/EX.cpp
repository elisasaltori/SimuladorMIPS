#include <string>

#include "include/IDEXE.hpp"
#include "include/EX.hpp"
#include "include/EXMEM.hpp"
#include "include/Mux.hpp"
#include "include/Ula.hpp"

using namespace std;

EX::EX(Ula *alu, IDEXE *idex, EXMEM *exmem) {
	this->alu = alu;
	this->idex = idex;
	this->exmem = exmem;

	this->ir = "";
	this->reg_dst = false;
	this->reg_write = false;
	this->alu_src = false;
	this->branch = false;
	this->mem_read = false;
	this->mem_write = false;
	this->mem_to_reg = false;
	this->alu_op = "";
}

void EX::write_signals() {
	exmem->set_reg_write(reg_write);
	exmem->set_branch(branch);
	exmem->set_mem_read(mem_read);
	exmem->set_mem_write(mem_write);
	exmem->set_mem_to_reg(mem_to_reg);
	exmem->set_ir(ir);
}

void EX::read_idex() {
	reg_dst = idex->getRegDest();
	reg_write = idex->getRegWrite();
	alu_src = idex->getAluSrc();
	branch = idex->getBranch();
	mem_read = idex->getMemRead();
	mem_write = idex->getMemWrite();
	mem_to_reg = idex->getMemToReg();
	alu_op = idex->getAluOP();
	ir = idex->getIR();
	npc = idex->getNPC();
	imm = idex->getImm();
	b = idex->getB();
	a = idex->getA();
	rt = idex->getRT();
	rd = idex->getRD();
}

void EX::read_tick(){
	read_idex();
}

void EX::write_tick() {
	Mux m = Mux(2);
	int select;

	exmem->set_branch_address(npc + (imm << 2));

	m.set_entrada(0, b);
	m.set_entrada(1, imm);
	select = alu_src == true ? 1 : 0;
	alu->set_aluIN1(a);

	alu->set_aluIN2(m.get_saida(select));
	alu->set_aluOP(alu_op);
	exmem->set_alu_out(alu->operation());
	if(exmem->get_alu_out() == 0)
		exmem->set_alu_zero(true);
	else
		exmem->set_alu_zero(false);

	exmem->set_alu_in2(b);
	m.set_entrada(0, rt);
	m.set_entrada(1, rd);
	select = reg_dst == true ? 1 : 0;
	exmem->set_write_reg_address(m.get_saida(select));
	
	write_signals();

}

/*
int main(void) {
	return 0;
}
*/