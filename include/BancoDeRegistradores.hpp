#ifndef BANCODEREGISTRADORES_HPP
#define BANCODEREGISTRADORES_HPP
#include "Registrador.hpp"

#define NREGISTRADORES 32
class BancoDeRegistradores{
	public:
		int read_reg1(int reg);
		void set_wreg(int reg);
		void set_wdata(int data);
		void reg_write();
		BancoDeRegistradores(int size);
	private:
		Registrador *banco;
		int write_register, write_data;
};
#endif