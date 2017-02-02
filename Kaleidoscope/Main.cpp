#include "llvm/ADT/STLExtras.h"


class Ast
{
public:
	Ast( const std::string & name )
	{
	}
};


int main()
{
	llvm::make_unique<Ast>( "aaa" );
	return 0;
}