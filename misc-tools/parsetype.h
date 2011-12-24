#ifndef PARSETYPE_H
#define PARSETYPE_H

#include <string>
#include <vector>
#include <iostream>

struct parse_t;

typedef std::string val_t;
typedef std::vector<parse_t> args_t;

typedef parse_t command;
typedef parse_t expr;
typedef parse_t test;

extern std::vector<command> program;

struct parse_t {
	val_t val;
	args_t args;
	char op;

	parse_t(): val(), args(), op('~') {};
	parse_t(args_t _args): val(), args(_args), op(' ') {};
	parse_t(val_t _val, args_t _args): val(_val), args(_args), op(' ') {};

	parse_t(val_t _val, parse_t arg1 = parse_t(),
	                    parse_t arg2 = parse_t(),
	                    parse_t arg3 = parse_t(),
	                    parse_t arg4 = parse_t())
	: val(_val), args(), op(' ')
	{
		if ( arg1.op!='~' ) args.push_back(arg1);
		if ( arg2.op!='~' ) args.push_back(arg2);
		if ( arg3.op!='~' ) args.push_back(arg3);
		if ( arg4.op!='~' ) args.push_back(arg4);
	};

	parse_t(char _op, parse_t arg1 = parse_t(),
	                  parse_t arg2 = parse_t(),
	                  parse_t arg3 = parse_t(),
	                  parse_t arg4 = parse_t())
	: val(), args(), op(_op)
	{
		if ( arg1.op!='~' ) args.push_back(arg1);
		if ( arg2.op!='~' ) args.push_back(arg2);
		if ( arg3.op!='~' ) args.push_back(arg3);
		if ( arg4.op!='~' ) args.push_back(arg4);
	}

	const val_t& name()  const { return val; }
	size_t       nargs() const { return args.size(); }

	operator std::string() { return val; }
	const char *c_str() { return val.c_str(); }
};

inline std::ostream &operator<<(std::ostream &out, const parse_t &obj)
{
	char op = obj.op;

	// '#' should never be output as operator
	switch ( op ) {
	case ' ': out << obj.val; op = ','; break;
	case 'n': out << '-';     op = '#'; break;
	case '!': out << '!';     op = '#'; break;
	case '(':                 op = '#'; break;
	case 'E': out << "ISEOF"; op = '#'; break;
	case 'M': out << "MATCH"; op = '#'; break;
	}

	// Special case compare operators, as these are not stored in 'op'
	if ( op=='?' ) {
		if ( obj.nargs()!=3 ) return out << "#error in compare#";
		out << obj.args[1] << obj.args[0] << obj.args[2];
		return out;
	}

	if ( obj.nargs()>0 ) {
		out << '(' << obj.args[0];
		for(size_t i=1; i<obj.nargs(); i++) out << op << obj.args[i];
		out << ')';
	}
    return out;
}

#endif
