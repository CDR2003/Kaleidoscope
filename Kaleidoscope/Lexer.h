#pragma once
#include <string>
#include <vector>


enum TokenType
{
	TT_Unknown = 0,
	TT_Eof = -1,
	TT_Def = -2,
	TT_Extern = -3,
	TT_Identifier = -4,
	TT_Number = -5,
};


struct Token
{
	Token( TokenType type, const std::string & text )
		: Type( type )
		, Text( text )
	{
	}

	TokenType Type;
	std::string Text;
};


class Lexer
{
public:
	Lexer();

	const std::string & GetText() const { return mText; }
	void SetText( const std::string & text );

	const std::vector<Token> & GetTokens() const { return mTokens; }

	void Run();

private:
	char NextChar();
	void AddToken( TokenType type, const std::string & text );

	std::string mText;
	std::vector<Token> mTokens;
	size_t mCurrentIndex;
};