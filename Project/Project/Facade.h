#pragma once
#include "iostream.h"


class TextEditor
{
public:
	void write_code()
	{
		cout << "TextEditor.write_code();" << endl;
	}
	void save()
	{
		cout << "TextEditor.save();" << endl;
	}
};

class Compiler
{
public:
	void compile()
	{
		cout << "Compiler.compile();" << endl;
	}
};

class Debugger
{
public:
	void execute()
	{
		cout << "Debugger.execute();" << endl;
	}

	void finish()
	{
		cout << "Debugger.finish();" << endl;
	}
};

class VSFacade
{
	TextEditor* text;
	Compiler* comp;
	Debugger* bug;
public:

	VSFacade( TextEditor* text,	Compiler* comp,	Debugger* bug ) : text(text), comp(comp), bug(bug){}

	void writeCode()
	{
		cout << "VSFacade.writeCode();" << endl;
		text->write_code();
		text->save();
	}

	void greenButton()
	{
		cout << "VSFacade.greenButton();" << endl;
		comp->compile();
		bug->execute();
		bug->finish();
	}
};
