#include "Lexer.h"
#include <cctype>


Lexer::Lexer()
	: mCurrentIndex( 0 )
{
}


void Lexer::SetText( const std::string & text )
{
	mText = text;
	mTokens.clear();
	mCurrentIndex = 0;
}


void Lexer::Run()
{
	auto lastChar = ' ';

	while( std::isspace( lastChar ) )
	{
		lastChar = this->NextChar();
	}

	if( std::isalpha( lastChar ) )
	{
		std::string str( 1, lastChar );

		for( ;;)
		{
			lastChar = this->NextChar();
			if( std::isalnum( lastChar ) == 0 )
			{
				break;
			}
			str += lastChar;
		}

		if( str == "def" )
		{
			this->AddToken( TT_Def, str );
		}
		else if( str == "extern" )
		{
			this->AddToken( TT_Extern, str );
		}
		else
		{
			this->AddToken( TT_Identifier, str );
		}
	}

	if( std::isdigit( lastChar ) || lastChar == '.' )
	{
		std::string str;
		do
		{
			str += lastChar;
			lastChar = this->NextChar();
		} while( isdigit( lastChar ) || lastChar == '.' );

		this->AddToken( TT_Number, str );
	}

	if( lastChar == '#' )
	{
		do
		{
			lastChar = this->NextChar();
		} while( lastChar != EOF && lastChar != '\n' && lastChar != '\r' );

		if( lastChar == EOF )
		{
			this->AddToken( TT_Eof, "" );
		}

		this->AddToken( TT_Unknown, std::string( 1, lastChar ) );
		lastChar = this->NextChar();
	}
}


char Lexer::NextChar()
{
	mCurrentIndex++;

	if( mCurrentIndex >= mText.size() )
	{
		return EOF;
	}

	return mText[mCurrentIndex];
}


void Lexer::AddToken( TokenType type, const std::string & text )
{
	mTokens.push_back( Token( type, text ) );
}