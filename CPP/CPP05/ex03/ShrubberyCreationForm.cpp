/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:30:51 by astutz            #+#    #+#             */
/*   Updated: 2024/06/18 10:43:27 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(): AForm("Shrubbery", false, 145, 137)
{
	_target = "default_target";
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target): AForm("Shrubbery", false, 145, 137), _target(target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src) : AForm(src)
{
	_target = src._target;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &rhs)
{
	if (this != &rhs)
	{
		_target = rhs._target;
		AForm::operator=(rhs);
	}
	return *this;
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() <= getGradeToExecute())
	{
		std::string fileName = _target + "_shrubbery";
		
		std::ofstream file(fileName.c_str());
		
		if (file.is_open())
		{
			file	<< "              _{\\ _{\\{\\/}/}/}__\"\n"
        			<< "             {/{/\\}{/{/\\}(\\}{/{/\\} _\"\n"
        			<< "            {/{/\\}{/{/\\}(_)/}{/{/\\}  _\"\n"
        			<< "         {\\{/(/\\}\\}{/{/\\}\\}{/){/\\}\\} /\\}\"\n"
        			<< "        {/{/(_)/}{\\{/)}\\}{\\(_){/}/}/}/}\"\n"
        			<< "       _{\\{/{/{\\{/{/(_)/}/}/}{\\(/}/}/}\"\n"
        			<< "      {/{/{\\{\\{\\(/}{\\{\\/}/}{\\}(_){\\/}\\}\"\n"
        			<< "      _{\\{/{\\{/(_)\\}/}{/{/{/\\}\\})\\}{/\\}\"\n"
        			<< "     {/{/{\\{\\(/}{/{\\{\\/})/}{\\(_)/}/}\\}\"\n"
        			<< "      {\\{\\/}(_){\\{\\{\\/}/}(_){\\/}{\\/}/})/}\"\n"
        			<< "       {/{\\{\\/}{/{\\{\\/}/}{\\{\\/}/}\\}(_)\"\n"
        			<< "      {/{\\{\\/}{/){\\{\\/}/}{\\{\\(/}/}\\}/}\"\n"
        			<< "       {/{\\{\\/}(_){\\{\\{(/}/}{\\(_)/}/}\\}\"\n"
        			<< "         {/({/{\\{/{\\{\\/}(_){\\/}/}\\}/}(\\}\"\n"
        			<< "          (_){/{\\/}{\\{\\/}/}{\\{\\)/}/}(_)\"\n"
        			<< "            {/{/{\\{\\/}{/{\\{\\{\\(_)/}\"\n"
        			<< "             {/{\\{\\{\\/}/}{\\{\\\\}/}\"\n"
        			<< "              {){/ {\\/}{\\/} \\}\\}\"\n"
        			<< "              	   \\.-'.- /\"\n"
        			<< "          __...--- |'-.-'| --...__\"\n"
        			<< "  _...--\\\"   .-'   |'-.-'|  ' -.  \\\"\"--..__\"\n"
        			<< " -\"    ' .  . '    |.'-._| '  . .  \\'   jro\"\n"
        			<< " .  '-  '    .--'  | '-.'|    .  '  . '\"\n"
        			<< "          ' ..     |'-_.-|\"\n"
        			<< "  .  '  .       _.-|-._ -|-._  .  '  .\"\n"
        			<< "              .'   |'- .-|   '.\"\n"
        			<< "  ..-'   ' .  '.   `-._.-�   .'  '  - .\"\n"
        			<< "   .-' '        '-._______.-'     '  .\"\n"
        			<< "        .      ~,\"\n"
        			<< "    .       .   |\\   .    ' '-.\"\n"
        			<< "    ___________/  \\____________\"\n"
        			<< "   /  Why is it, when you want \\ \"\n"
        			<< "  |  something, it is so damn   |\"\n"
        			<< "  |    much work to get it?     |\"\n"
        			<< "   \\___________________________/\"";
		}
		else
		{
			std::cerr << "Failed to create " << fileName << std::endl;
			return;
		}
		file.close();
	}
	else
		throw GradeTooLowException();
}
