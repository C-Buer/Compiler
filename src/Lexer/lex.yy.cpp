// lex.yy.cpp generated by reflex 5.0.1 from src/Lexer/Lexer.l

#define REFLEX_VERSION "5.0.1"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  OPTIONS USED                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define REFLEX_OPTION_bison true
#define REFLEX_OPTION_flex true
#define REFLEX_OPTION_lex yylex
#define REFLEX_OPTION_lexer yyFlexLexer
#define REFLEX_OPTION_noyywrap true
#define REFLEX_OPTION_outfile "lex.yy.cpp"
#define REFLEX_OPTION_prefix yy
#define REFLEX_OPTION_unicode true

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  FLEX-COMPATIBLE DEFINITIONS                                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define INITIAL (0)
#define YY_NUM_RULES (45)

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  REGEX MATCHER                                                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/matcher.h>

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  FLEX-COMPATIBLE ABSTRACT LEXER CLASS                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <reflex/flexlexer.h>
typedef reflex::FlexLexer<reflex::Matcher> FlexLexer;
#undef yytext
#undef yyleng
#undef yylineno

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  LEXER CLASS                                                               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

class yyFlexLexer : public FlexLexer
{
  public:
    yyFlexLexer(
        // a persistent source of input, empty by default
        const reflex::Input &input = reflex::Input(),
        // optional output stream, NULL means std::cout by default
        std::ostream *os = NULL)
        : FlexLexer(input, os)
    {
    }
    // the flex lexer function defined by SECTION 2
    virtual int yylex(void);
    // lexer functions accepting new input to scan
    int yylex(const reflex::Input &input)
    {
        in(input);
        return yylex();
    }
    int yylex(const reflex::Input &input, std::ostream *os)
    {
        in(input);
        if (os)
            out(*os);
        return yylex();
    }
};

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 1: %{ user code %}                                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 3 "src/Lexer/Lexer.l"

#include "Token.hpp"
#include <string>
#include <unordered_map>
#include <vector>

static int line = 1;
static int col = 1;
static std::vector<Token> tokens;

static void addToken(TokenType type, const std::string &lexeme)
{
    tokens.emplace_back(type, lexeme, line, col);
    col += static_cast<int>(lexeme.size());
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  BISON                                                                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

yyFlexLexer YY_SCANNER;

#ifndef YY_EXTERN_C
#define YY_EXTERN_C
#endif

char *yytext;
yy_size_t yyleng;
int yylineno;

YY_EXTERN_C int yylex(void)
{
    int yylex_token = YY_SCANNER.yylex();
    yytext = const_cast<char *>(YY_SCANNER.YYText());
    yyleng = static_cast<yy_size_t>(YY_SCANNER.YYLeng());
    yylineno = static_cast<int>(YY_SCANNER.lineno());
    return yylex_token;
}

#define yytext const_cast<char *>(YY_SCANNER.YYText())
#define yyleng static_cast<yy_size_t>(YY_SCANNER.YYLeng())
#define yylineno static_cast<int>(YY_SCANNER.lineno())

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 2: rules                                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int yyFlexLexer::yylex(void)
{
    static const char *REGEX_INITIAL =
        "(?m)([\\x0a\\x0d]+)|([\\x09\\x20]+)|((?:\\Q(\\E))|((?:\\Q)\\E))|((?:\\Q{\\E))|((?:\\Q}\\E))|((?:\\Q[\\E))|((?:"
        "\\Q]\\E))|((?:\\Q,\\E))|((?:\\Q.\\E))|((?:\\Q;\\E))|((?:\\Q:\\E))|((?:\\Q+\\E))|((?:\\Q-\\E))|((?:\\Q*\\E))|(("
        "?:\\Q/"
        "\\E))|((?:\\Q%\\E))|((?:\\Q&\\E))|((?:\\Q|\\E))|((?:\\Q^\\E))|((?:\\Q!\\E))|((?:\\Q~\\E))|((?:\\Q?\\E))|((?:"
        "\\Q<\\E))|((?:\\Q>\\E))|((?:\\Q=\\E))|((?:\\Q==\\E))|((?:\\Q!=\\E))|((?:\\Q<=\\E))|((?:\\Q>=\\E))|((?:\\Q&&"
        "\\E))|((?:\\Q||\\E))|((?:\\Q->\\E))|((?:\\Q::\\E))|((?:\\Q++\\E))|((?:\\Q--\\E))|((?:\\Q<<\\E))|((?:\\Q>>\\E))"
        "|((?:\\Q...\\E))|(\"(?:(?:[\\x00-!]|[\\x23-\\x5b]|[\\x5d-\\x7f]|[\\xc2-\\xdf][\\x80-\\xbf]|\\xe0[\\xa0-\\xbf]["
        "\\x80-\\xbf]|[\\xe1-\\xec][\\x80-\\xbf][\\x80-\\xbf]|\\xed[\\x80-\\x9f][\\x80-\\xbf]|[\\xee\\xef][\\x80-\\xbf]"
        "[\\x80-\\xbf]|\\xf0[\\x90-\\xbf][\\x80-\\xbf][\\x80-\\xbf]|[\\xf1-\\xf3][\\x80-\\xbf][\\x80-\\xbf][\\x80-"
        "\\xbf]|\\xf4[\\x80-\\x8f][\\x80-\\xbf][\\x80-\\xbf])|\\\\(?:.[\\x80-\\xbf]*))*\")|('(?:(?:[\\x00-&]|[(-\\x5b]|"
        "[\\x5d-\\x7f]|[\\xc2-\\xdf][\\x80-\\xbf]|\\xe0[\\xa0-\\xbf][\\x80-\\xbf]|[\\xe1-\\xec][\\x80-\\xbf][\\x80-"
        "\\xbf]|\\xed[\\x80-\\x9f][\\x80-\\xbf]|[\\xee\\xef][\\x80-\\xbf][\\x80-\\xbf]|\\xf0[\\x90-\\xbf][\\x80-\\xbf]["
        "\\x80-\\xbf]|[\\xf1-\\xf3][\\x80-\\xbf][\\x80-\\xbf][\\x80-\\xbf]|\\xf4[\\x80-\\x8f][\\x80-\\xbf][\\x80-\\xbf]"
        ")|\\\\(?:.[\\x80-\\xbf]*))*')|([0-9]+(?:\\.[0-9]+))|([0-9]+)|((?:[A-Z]|_|[a-z]|\\xc2\\xb5|\\xc3[\\x80-\\x96]|"
        "\\xc3[\\x98-\\xb6]|\\xc3[\\xb8-\\xbf]|[\\xc4\\xc5][\\x80-\\xbf]|\\xc6[\\x80-\\xba]|\\xc6[\\xbc-\\xbf]|"
        "\\xc7\\x84|\\xc7[\\x86\\x87]|\\xc7[\\x89\\x8a]|\\xc7[\\x8c-\\xb1]|\\xc7[\\xb3-\\xbf]|[\\xc8\\xc9][\\x80-\\xbf]"
        "|\\xca[\\x80-\\x93]|\\xca[\\x95-\\xaf]|\\xcd[\\xb0-\\xb3]|\\xcd[\\xb6\\xb7]|\\xcd[\\xbb-\\xbd]|\\xcd\\xbf|"
        "\\xce\\x86|\\xce[\\x88-\\x8a]|\\xce\\x8c|\\xce[\\x8e-\\xa1]|\\xce[\\xa3-\\xbf]|\\xcf[\\x80-\\xb5]|\\xcf[\\xb7-"
        "\\xbf]|[\\xd0\\xd1][\\x80-\\xbf]|\\xd2[\\x80\\x81]|\\xd2[\\x8a-\\xbf]|\\xd3[\\x80-\\xbf]|\\xd4[\\x80-\\xaf]|"
        "\\xd4[\\xb1-\\xbf]|\\xd5[\\x80-\\x96]|\\xd5[\\xa0-\\xbf]|\\xd6[\\x80-\\x88]|\\xe1(?:\\x82[\\xa0-\\xbf]|\\x83["
        "\\x80-\\x85])|\\xe1\\x83\\x87|\\xe1\\x83\\x8d|\\xe1\\x83[\\x90-\\xba]|\\xe1\\x83[\\xbd-\\xbf]|\\xe1(?:\\x8e["
        "\\xa0-\\xbf]|\\x8f[\\x80-\\xb5])|\\xe1\\x8f[\\xb8-\\xbd]|\\xe1\\xb2[\\x80-\\x88]|\\xe1\\xb2[\\x90-\\xba]|"
        "\\xe1\\xb2[\\xbd-\\xbf]|\\xe1\\xb4[\\x80-\\xab]|\\xe1\\xb5[\\xab-\\xb7]|\\xe1(?:\\xb5[\\xb9-\\xbf]|\\xb6["
        "\\x80-\\x9a])|\\xe1(?:[\\xb8-\\xbb][\\x80-\\xbf]|\\xbc[\\x80-\\x95])|\\xe1\\xbc[\\x98-\\x9d]|\\xe1(?:\\xbc["
        "\\xa0-\\xbf]|\\xbd[\\x80-\\x85])|\\xe1\\xbd[\\x88-\\x8d]|\\xe1\\xbd[\\x90-\\x97]|\\xe1\\xbd\\x99|"
        "\\xe1\\xbd\\x9b|\\xe1\\xbd\\x9d|\\xe1\\xbd[\\x9f-\\xbd]|\\xe1\\xbe[\\x80-\\x87]|\\xe1\\xbe[\\x90-\\x97]|"
        "\\xe1\\xbe[\\xa0-\\xa7]|\\xe1\\xbe[\\xb0-\\xb4]|\\xe1\\xbe[\\xb6-\\xbb]|\\xe1\\xbe\\xbe|\\xe1\\xbf[\\x82-"
        "\\x84]|\\xe1\\xbf[\\x86-\\x8b]|\\xe1\\xbf[\\x90-\\x93]|\\xe1\\xbf[\\x96-\\x9b]|\\xe1\\xbf[\\xa0-\\xac]|"
        "\\xe1\\xbf[\\xb2-\\xb4]|\\xe1\\xbf[\\xb6-\\xbb]|\\xe2\\x84\\x82|\\xe2\\x84\\x87|\\xe2\\x84[\\x8a-\\x93]|"
        "\\xe2\\x84\\x95|\\xe2\\x84[\\x99-\\x9d]|\\xe2\\x84\\xa4|\\xe2\\x84\\xa6|\\xe2\\x84\\xa8|\\xe2\\x84[\\xaa-"
        "\\xad]|\\xe2\\x84[\\xaf-\\xb4]|\\xe2\\x84\\xb9|\\xe2\\x84[\\xbc-\\xbf]|\\xe2\\x85[\\x85-\\x89]|"
        "\\xe2\\x85\\x8e|\\xe2\\x86[\\x83\\x84]|\\xe2(?:\\xb0[\\x80-\\xbf]|\\xb1[\\x80-\\xbb])|\\xe2(?:\\xb1["
        "\\xbe\\xbf]|\\xb2[\\x80-\\xbf]|\\xb3[\\x80-\\xa4])|\\xe2\\xb3[\\xab-\\xae]|\\xe2\\xb3[\\xb2\\xb3]|\\xe2\\xb4["
        "\\x80-\\xa5]|\\xe2\\xb4\\xa7|\\xe2\\xb4\\xad|\\xea\\x99[\\x80-\\xad]|\\xea\\x9a[\\x80-\\x9b]|\\xea(?:\\x9c["
        "\\xa2-\\xbf]|\\x9d[\\x80-\\xaf])|\\xea(?:\\x9d[\\xb1-\\xbf]|\\x9e[\\x80-\\x87])|\\xea\\x9e[\\x8b-\\x8e]|\\xea("
        "?:\\x9e[\\x90-\\xbf]|\\x9f[\\x80-\\x8a])|\\xea\\x9f[\\x90\\x91]|\\xea\\x9f\\x93|\\xea\\x9f[\\x95-\\x99]|"
        "\\xea\\x9f[\\xb5\\xb6]|\\xea\\x9f\\xba|\\xea(?:\\xac[\\xb0-\\xbf]|\\xad[\\x80-\\x9a])|\\xea\\xad[\\xa0-\\xa8]|"
        "\\xea(?:\\xad[\\xb0-\\xbf]|\\xae[\\x80-\\xbf])|\\xef\\xac[\\x80-\\x86]|\\xef\\xac[\\x93-\\x97]|\\xef\\xbc["
        "\\xa1-\\xba]|\\xef\\xbd[\\x81-\\x9a]|\\xf0\\x90(?:\\x90[\\x80-\\xbf]|\\x91[\\x80-\\x8f])|\\xf0\\x90(?:\\x92["
        "\\xb0-\\xbf]|\\x93[\\x80-\\x93])|\\xf0\\x90\\x93[\\x98-\\xbb]|\\xf0\\x90\\x95[\\xb0-\\xba]|\\xf0\\x90(?:\\x95["
        "\\xbc-\\xbf]|\\x96[\\x80-\\x8a])|\\xf0\\x90\\x96[\\x8c-\\x92]|\\xf0\\x90\\x96[\\x94\\x95]|\\xf0\\x90\\x96["
        "\\x97-\\xa1]|\\xf0\\x90\\x96[\\xa3-\\xb1]|\\xf0\\x90\\x96[\\xb3-\\xb9]|\\xf0\\x90\\x96[\\xbb\\xbc]|"
        "\\xf0\\x90\\xb2[\\x80-\\xb2]|\\xf0\\x90\\xb3[\\x80-\\xb2]|\\xf0\\x91(?:\\xa2[\\xa0-\\xbf]|\\xa3[\\x80-\\x9f])|"
        "\\xf0\\x96\\xb9[\\x80-\\xbf]|\\xf0\\x9d(?:\\x90[\\x80-\\xbf]|\\x91[\\x80-\\x94])|\\xf0\\x9d(?:\\x91[\\x96-"
        "\\xbf]|\\x92[\\x80-\\x9c])|\\xf0\\x9d\\x92[\\x9e\\x9f]|\\xf0\\x9d\\x92\\xa2|\\xf0\\x9d\\x92[\\xa5\\xa6]|"
        "\\xf0\\x9d\\x92[\\xa9-\\xac]|\\xf0\\x9d\\x92[\\xae-\\xb9]|\\xf0\\x9d\\x92\\xbb|\\xf0\\x9d(?:\\x92[\\xbd-\\xbf]"
        "|\\x93[\\x80-\\x83])|\\xf0\\x9d(?:\\x93[\\x85-\\xbf]|\\x94[\\x80-\\x85])|\\xf0\\x9d\\x94[\\x87-\\x8a]|"
        "\\xf0\\x9d\\x94[\\x8d-\\x94]|\\xf0\\x9d\\x94[\\x96-\\x9c]|\\xf0\\x9d\\x94[\\x9e-\\xb9]|\\xf0\\x9d\\x94[\\xbb-"
        "\\xbe]|\\xf0\\x9d\\x95[\\x80-\\x84]|\\xf0\\x9d\\x95\\x86|\\xf0\\x9d\\x95[\\x8a-\\x90]|\\xf0\\x9d(?:\\x95["
        "\\x92-\\xbf]|[\\x96-\\x99][\\x80-\\xbf]|\\x9a[\\x80-\\xa5])|\\xf0\\x9d(?:\\x9a[\\xa8-\\xbf]|\\x9b\\x80)|"
        "\\xf0\\x9d\\x9b[\\x82-\\x9a]|\\xf0\\x9d\\x9b[\\x9c-\\xba]|\\xf0\\x9d(?:\\x9b[\\xbc-\\xbf]|\\x9c[\\x80-\\x94])|"
        "\\xf0\\x9d\\x9c[\\x96-\\xb4]|\\xf0\\x9d(?:\\x9c[\\xb6-\\xbf]|\\x9d[\\x80-\\x8e])|\\xf0\\x9d\\x9d[\\x90-\\xae]|"
        "\\xf0\\x9d(?:\\x9d[\\xb0-\\xbf]|\\x9e[\\x80-\\x88])|\\xf0\\x9d\\x9e[\\x8a-\\xa8]|\\xf0\\x9d(?:\\x9e[\\xaa-"
        "\\xbf]|\\x9f[\\x80-\\x82])|\\xf0\\x9d\\x9f[\\x84-\\x8b]|\\xf0\\x9d\\xbc[\\x80-\\x89]|\\xf0\\x9d\\xbc[\\x8b-"
        "\\x9e]|\\xf0\\x9d\\xbc[\\xa5-\\xaa]|\\xf0\\x9e(?:\\xa4[\\x80-\\xbf]|\\xa5[\\x80-\\x83]))(?:[0-9]|[A-Z]|_|[a-z]"
        "|\\xc2\\xb5|\\xc3[\\x80-\\x96]|\\xc3[\\x98-\\xb6]|\\xc3[\\xb8-\\xbf]|[\\xc4\\xc5][\\x80-\\xbf]|\\xc6[\\x80-"
        "\\xba]|\\xc6[\\xbc-\\xbf]|\\xc7\\x84|\\xc7[\\x86\\x87]|\\xc7[\\x89\\x8a]|\\xc7[\\x8c-\\xb1]|\\xc7[\\xb3-\\xbf]"
        "|[\\xc8\\xc9][\\x80-\\xbf]|\\xca[\\x80-\\x93]|\\xca[\\x95-\\xaf]|\\xcd[\\xb0-\\xb3]|\\xcd[\\xb6\\xb7]|\\xcd["
        "\\xbb-\\xbd]|\\xcd\\xbf|\\xce\\x86|\\xce[\\x88-\\x8a]|\\xce\\x8c|\\xce[\\x8e-\\xa1]|\\xce[\\xa3-\\xbf]|\\xcf["
        "\\x80-\\xb5]|\\xcf[\\xb7-\\xbf]|[\\xd0\\xd1][\\x80-\\xbf]|\\xd2[\\x80\\x81]|\\xd2[\\x8a-\\xbf]|\\xd3[\\x80-"
        "\\xbf]|\\xd4[\\x80-\\xaf]|\\xd4[\\xb1-\\xbf]|\\xd5[\\x80-\\x96]|\\xd5[\\xa0-\\xbf]|\\xd6[\\x80-\\x88]|\\xd9["
        "\\xa0-\\xa9]|\\xdb[\\xb0-\\xb9]|\\xdf[\\x80-\\x89]|\\xe0\\xa5[\\xa6-\\xaf]|\\xe0\\xa7[\\xa6-\\xaf]|\\xe0\\xa9["
        "\\xa6-\\xaf]|\\xe0\\xab[\\xa6-\\xaf]|\\xe0\\xad[\\xa6-\\xaf]|\\xe0\\xaf[\\xa6-\\xaf]|\\xe0\\xb1[\\xa6-\\xaf]|"
        "\\xe0\\xb3[\\xa6-\\xaf]|\\xe0\\xb5[\\xa6-\\xaf]|\\xe0\\xb7[\\xa6-\\xaf]|\\xe0\\xb9[\\x90-\\x99]|\\xe0\\xbb["
        "\\x90-\\x99]|\\xe0\\xbc[\\xa0-\\xa9]|\\xe1\\x81[\\x80-\\x89]|\\xe1\\x82[\\x90-\\x99]|\\xe1(?:\\x82[\\xa0-"
        "\\xbf]|\\x83[\\x80-\\x85])|\\xe1\\x83\\x87|\\xe1\\x83\\x8d|\\xe1\\x83[\\x90-\\xba]|\\xe1\\x83[\\xbd-\\xbf]|"
        "\\xe1(?:\\x8e[\\xa0-\\xbf]|\\x8f[\\x80-\\xb5])|\\xe1\\x8f[\\xb8-\\xbd]|\\xe1\\x9f[\\xa0-\\xa9]|\\xe1\\xa0["
        "\\x90-\\x99]|\\xe1\\xa5[\\x86-\\x8f]|\\xe1\\xa7[\\x90-\\x99]|\\xe1\\xaa[\\x80-\\x89]|\\xe1\\xaa[\\x90-\\x99]|"
        "\\xe1\\xad[\\x90-\\x99]|\\xe1\\xae[\\xb0-\\xb9]|\\xe1\\xb1[\\x80-\\x89]|\\xe1\\xb1[\\x90-\\x99]|\\xe1\\xb2["
        "\\x80-\\x88]|\\xe1\\xb2[\\x90-\\xba]|\\xe1\\xb2[\\xbd-\\xbf]|\\xe1\\xb4[\\x80-\\xab]|\\xe1\\xb5[\\xab-\\xb7]|"
        "\\xe1(?:\\xb5[\\xb9-\\xbf]|\\xb6[\\x80-\\x9a])|\\xe1(?:[\\xb8-\\xbb][\\x80-\\xbf]|\\xbc[\\x80-\\x95])|"
        "\\xe1\\xbc[\\x98-\\x9d]|\\xe1(?:\\xbc[\\xa0-\\xbf]|\\xbd[\\x80-\\x85])|\\xe1\\xbd[\\x88-\\x8d]|\\xe1\\xbd["
        "\\x90-\\x97]|\\xe1\\xbd\\x99|\\xe1\\xbd\\x9b|\\xe1\\xbd\\x9d|\\xe1\\xbd[\\x9f-\\xbd]|\\xe1\\xbe[\\x80-\\x87]|"
        "\\xe1\\xbe[\\x90-\\x97]|\\xe1\\xbe[\\xa0-\\xa7]|\\xe1\\xbe[\\xb0-\\xb4]|\\xe1\\xbe[\\xb6-\\xbb]|"
        "\\xe1\\xbe\\xbe|\\xe1\\xbf[\\x82-\\x84]|\\xe1\\xbf[\\x86-\\x8b]|\\xe1\\xbf[\\x90-\\x93]|\\xe1\\xbf[\\x96-"
        "\\x9b]|\\xe1\\xbf[\\xa0-\\xac]|\\xe1\\xbf[\\xb2-\\xb4]|\\xe1\\xbf[\\xb6-\\xbb]|\\xe2\\x84\\x82|"
        "\\xe2\\x84\\x87|\\xe2\\x84[\\x8a-\\x93]|\\xe2\\x84\\x95|\\xe2\\x84[\\x99-\\x9d]|\\xe2\\x84\\xa4|"
        "\\xe2\\x84\\xa6|\\xe2\\x84\\xa8|\\xe2\\x84[\\xaa-\\xad]|\\xe2\\x84[\\xaf-\\xb4]|\\xe2\\x84\\xb9|\\xe2\\x84["
        "\\xbc-\\xbf]|\\xe2\\x85[\\x85-\\x89]|\\xe2\\x85\\x8e|\\xe2\\x86[\\x83\\x84]|\\xe2(?:\\xb0[\\x80-\\xbf]|\\xb1["
        "\\x80-\\xbb])|\\xe2(?:\\xb1[\\xbe\\xbf]|\\xb2[\\x80-\\xbf]|\\xb3[\\x80-\\xa4])|\\xe2\\xb3[\\xab-\\xae]|"
        "\\xe2\\xb3[\\xb2\\xb3]|\\xe2\\xb4[\\x80-\\xa5]|\\xe2\\xb4\\xa7|\\xe2\\xb4\\xad|\\xea\\x98[\\xa0-\\xa9]|"
        "\\xea\\x99[\\x80-\\xad]|\\xea\\x9a[\\x80-\\x9b]|\\xea(?:\\x9c[\\xa2-\\xbf]|\\x9d[\\x80-\\xaf])|\\xea(?:\\x9d["
        "\\xb1-\\xbf]|\\x9e[\\x80-\\x87])|\\xea\\x9e[\\x8b-\\x8e]|\\xea(?:\\x9e[\\x90-\\xbf]|\\x9f[\\x80-\\x8a])|"
        "\\xea\\x9f[\\x90\\x91]|\\xea\\x9f\\x93|\\xea\\x9f[\\x95-\\x99]|\\xea\\x9f[\\xb5\\xb6]|\\xea\\x9f\\xba|"
        "\\xea\\xa3[\\x90-\\x99]|\\xea\\xa4[\\x80-\\x89]|\\xea\\xa7[\\x90-\\x99]|\\xea\\xa7[\\xb0-\\xb9]|\\xea\\xa9["
        "\\x90-\\x99]|\\xea(?:\\xac[\\xb0-\\xbf]|\\xad[\\x80-\\x9a])|\\xea\\xad[\\xa0-\\xa8]|\\xea(?:\\xad[\\xb0-\\xbf]"
        "|\\xae[\\x80-\\xbf])|\\xea\\xaf[\\xb0-\\xb9]|\\xef\\xac[\\x80-\\x86]|\\xef\\xac[\\x93-\\x97]|\\xef\\xbc[\\x90-"
        "\\x99]|\\xef\\xbc[\\xa1-\\xba]|\\xef\\xbd[\\x81-\\x9a]|\\xf0\\x90(?:\\x90[\\x80-\\xbf]|\\x91[\\x80-\\x8f])|"
        "\\xf0\\x90\\x92[\\xa0-\\xa9]|\\xf0\\x90(?:\\x92[\\xb0-\\xbf]|\\x93[\\x80-\\x93])|\\xf0\\x90\\x93[\\x98-\\xbb]|"
        "\\xf0\\x90\\x95[\\xb0-\\xba]|\\xf0\\x90(?:\\x95[\\xbc-\\xbf]|\\x96[\\x80-\\x8a])|\\xf0\\x90\\x96[\\x8c-\\x92]|"
        "\\xf0\\x90\\x96[\\x94\\x95]|\\xf0\\x90\\x96[\\x97-\\xa1]|\\xf0\\x90\\x96[\\xa3-\\xb1]|\\xf0\\x90\\x96[\\xb3-"
        "\\xb9]|\\xf0\\x90\\x96[\\xbb\\xbc]|\\xf0\\x90\\xb2[\\x80-\\xb2]|\\xf0\\x90\\xb3[\\x80-\\xb2]|\\xf0\\x90\\xb4["
        "\\xb0-\\xb9]|\\xf0\\x91\\x81[\\xa6-\\xaf]|\\xf0\\x91\\x83[\\xb0-\\xb9]|\\xf0\\x91\\x84[\\xb6-\\xbf]|"
        "\\xf0\\x91\\x87[\\x90-\\x99]|\\xf0\\x91\\x8b[\\xb0-\\xb9]|\\xf0\\x91\\x91[\\x90-\\x99]|\\xf0\\x91\\x93[\\x90-"
        "\\x99]|\\xf0\\x91\\x99[\\x90-\\x99]|\\xf0\\x91\\x9b[\\x80-\\x89]|\\xf0\\x91\\x9c[\\xb0-\\xb9]|\\xf0\\x91(?:"
        "\\xa2[\\xa0-\\xbf]|\\xa3[\\x80-\\xa9])|\\xf0\\x91\\xa5[\\x90-\\x99]|\\xf0\\x91\\xb1[\\x90-\\x99]|"
        "\\xf0\\x91\\xb5[\\x90-\\x99]|\\xf0\\x91\\xb6[\\xa0-\\xa9]|\\xf0\\x91\\xbd[\\x90-\\x99]|\\xf0\\x96\\xa9[\\xa0-"
        "\\xa9]|\\xf0\\x96\\xab[\\x80-\\x89]|\\xf0\\x96\\xad[\\x90-\\x99]|\\xf0\\x96\\xb9[\\x80-\\xbf]|\\xf0\\x9d(?:"
        "\\x90[\\x80-\\xbf]|\\x91[\\x80-\\x94])|\\xf0\\x9d(?:\\x91[\\x96-\\xbf]|\\x92[\\x80-\\x9c])|\\xf0\\x9d\\x92["
        "\\x9e\\x9f]|\\xf0\\x9d\\x92\\xa2|\\xf0\\x9d\\x92[\\xa5\\xa6]|\\xf0\\x9d\\x92[\\xa9-\\xac]|\\xf0\\x9d\\x92["
        "\\xae-\\xb9]|\\xf0\\x9d\\x92\\xbb|\\xf0\\x9d(?:\\x92[\\xbd-\\xbf]|\\x93[\\x80-\\x83])|\\xf0\\x9d(?:\\x93["
        "\\x85-\\xbf]|\\x94[\\x80-\\x85])|\\xf0\\x9d\\x94[\\x87-\\x8a]|\\xf0\\x9d\\x94[\\x8d-\\x94]|\\xf0\\x9d\\x94["
        "\\x96-\\x9c]|\\xf0\\x9d\\x94[\\x9e-\\xb9]|\\xf0\\x9d\\x94[\\xbb-\\xbe]|\\xf0\\x9d\\x95[\\x80-\\x84]|"
        "\\xf0\\x9d\\x95\\x86|\\xf0\\x9d\\x95[\\x8a-\\x90]|\\xf0\\x9d(?:\\x95[\\x92-\\xbf]|[\\x96-\\x99][\\x80-\\xbf]|"
        "\\x9a[\\x80-\\xa5])|\\xf0\\x9d(?:\\x9a[\\xa8-\\xbf]|\\x9b\\x80)|\\xf0\\x9d\\x9b[\\x82-\\x9a]|\\xf0\\x9d\\x9b["
        "\\x9c-\\xba]|\\xf0\\x9d(?:\\x9b[\\xbc-\\xbf]|\\x9c[\\x80-\\x94])|\\xf0\\x9d\\x9c[\\x96-\\xb4]|\\xf0\\x9d(?:"
        "\\x9c[\\xb6-\\xbf]|\\x9d[\\x80-\\x8e])|\\xf0\\x9d\\x9d[\\x90-\\xae]|\\xf0\\x9d(?:\\x9d[\\xb0-\\xbf]|\\x9e["
        "\\x80-\\x88])|\\xf0\\x9d\\x9e[\\x8a-\\xa8]|\\xf0\\x9d(?:\\x9e[\\xaa-\\xbf]|\\x9f[\\x80-\\x82])|"
        "\\xf0\\x9d\\x9f[\\x84-\\x8b]|\\xf0\\x9d\\x9f[\\x8e-\\xbf]|\\xf0\\x9d\\xbc[\\x80-\\x89]|\\xf0\\x9d\\xbc[\\x8b-"
        "\\x9e]|\\xf0\\x9d\\xbc[\\xa5-\\xaa]|\\xf0\\x9e\\x85[\\x80-\\x89]|\\xf0\\x9e\\x8b[\\xb0-\\xb9]|\\xf0\\x9e\\x93["
        "\\xb0-\\xb9]|\\xf0\\x9e(?:\\xa4[\\x80-\\xbf]|\\xa5[\\x80-\\x83])|\\xf0\\x9e\\xa5[\\x90-\\x99]|\\xf0\\x9f\\xaf["
        "\\xb0-\\xb9])*)|((?:.[\\x80-\\xbf]*))";
    static const reflex::Pattern PATTERN_INITIAL(REGEX_INITIAL);
    if (!has_matcher())
    {
        matcher(new Matcher(PATTERN_INITIAL, stdinit(), this));
        YY_USER_INIT
    }
    while (true)
    {
        switch (matcher().scan())
        {
        case 0:
            if (matcher().at_end())
            {
                yyterminate();
            }
            else
            {
                output(matcher().input());
            }
            YY_BREAK
        case 1: // rule src/Lexer/Lexer.l:21: [\r\n]+ :
            YY_USER_ACTION
#line 21 "src/Lexer/Lexer.l"
            {
                line += yyleng;
                col = 1;
            }

            YY_BREAK
        case 2: // rule src/Lexer/Lexer.l:26: [ \t]+ :
            YY_USER_ACTION
#line 26 "src/Lexer/Lexer.l"
            {
                col += yyleng;
            }

            YY_BREAK
        case 3: // rule src/Lexer/Lexer.l:31: "(" :
            YY_USER_ACTION
#line 31 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::LeftParen, yytext);
            }
            YY_BREAK
        case 4: // rule src/Lexer/Lexer.l:32: ")" :
            YY_USER_ACTION
#line 32 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::RightParen, yytext);
            }
            YY_BREAK
        case 5: // rule src/Lexer/Lexer.l:33: "{" :
            YY_USER_ACTION
#line 33 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::LeftBrace, yytext);
            }
            YY_BREAK
        case 6: // rule src/Lexer/Lexer.l:34: "}" :
            YY_USER_ACTION
#line 34 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::RightBrace, yytext);
            }
            YY_BREAK
        case 7: // rule src/Lexer/Lexer.l:35: "[" :
            YY_USER_ACTION
#line 35 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::LeftBracket, yytext);
            }
            YY_BREAK
        case 8: // rule src/Lexer/Lexer.l:36: "]" :
            YY_USER_ACTION
#line 36 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::RightBracket, yytext);
            }
            YY_BREAK
        case 9: // rule src/Lexer/Lexer.l:37: "," :
            YY_USER_ACTION
#line 37 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Comma, yytext);
            }
            YY_BREAK
        case 10: // rule src/Lexer/Lexer.l:38: "." :
            YY_USER_ACTION
#line 38 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Dot, yytext);
            }
            YY_BREAK
        case 11: // rule src/Lexer/Lexer.l:39: ";" :
            YY_USER_ACTION
#line 39 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Semicolon, yytext);
            }
            YY_BREAK
        case 12: // rule src/Lexer/Lexer.l:40: ":" :
            YY_USER_ACTION
#line 40 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Colon, yytext);
            }
            YY_BREAK
        case 13: // rule src/Lexer/Lexer.l:41: "+" :
            YY_USER_ACTION
#line 41 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Plus, yytext);
            }
            YY_BREAK
        case 14: // rule src/Lexer/Lexer.l:42: "-" :
            YY_USER_ACTION
#line 42 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Minus, yytext);
            }
            YY_BREAK
        case 15: // rule src/Lexer/Lexer.l:43: "*" :
            YY_USER_ACTION
#line 43 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Star, yytext);
            }
            YY_BREAK
        case 16: // rule src/Lexer/Lexer.l:44: "/" :
            YY_USER_ACTION
#line 44 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Slash, yytext);
            }
            YY_BREAK
        case 17: // rule src/Lexer/Lexer.l:45: "%" :
            YY_USER_ACTION
#line 45 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Percent, yytext);
            }
            YY_BREAK
        case 18: // rule src/Lexer/Lexer.l:46: "&" :
            YY_USER_ACTION
#line 46 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Ampersand, yytext);
            }
            YY_BREAK
        case 19: // rule src/Lexer/Lexer.l:47: "|" :
            YY_USER_ACTION
#line 47 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Pipe, yytext);
            }
            YY_BREAK
        case 20: // rule src/Lexer/Lexer.l:48: "^" :
            YY_USER_ACTION
#line 48 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Caret, yytext);
            }
            YY_BREAK
        case 21: // rule src/Lexer/Lexer.l:49: "!" :
            YY_USER_ACTION
#line 49 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Exclamation, yytext);
            }
            YY_BREAK
        case 22: // rule src/Lexer/Lexer.l:50: "~" :
            YY_USER_ACTION
#line 50 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Tilde, yytext);
            }
            YY_BREAK
        case 23: // rule src/Lexer/Lexer.l:51: "?" :
            YY_USER_ACTION
#line 51 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Question, yytext);
            }
            YY_BREAK
        case 24: // rule src/Lexer/Lexer.l:52: "<" :
            YY_USER_ACTION
#line 52 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Less, yytext);
            }
            YY_BREAK
        case 25: // rule src/Lexer/Lexer.l:53: ">" :
            YY_USER_ACTION
#line 53 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Greater, yytext);
            }
            YY_BREAK
        case 26: // rule src/Lexer/Lexer.l:54: "=" :
            YY_USER_ACTION
#line 54 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Equals, yytext);
            }

            YY_BREAK
        case 27: // rule src/Lexer/Lexer.l:57: "==" :
            YY_USER_ACTION
#line 57 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::DoubleEquals, yytext);
            }
            YY_BREAK
        case 28: // rule src/Lexer/Lexer.l:58: "!=" :
            YY_USER_ACTION
#line 58 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::NotEquals, yytext);
            }
            YY_BREAK
        case 29: // rule src/Lexer/Lexer.l:59: "<=" :
            YY_USER_ACTION
#line 59 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::LessEquals, yytext);
            }
            YY_BREAK
        case 30: // rule src/Lexer/Lexer.l:60: ">=" :
            YY_USER_ACTION
#line 60 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::GreaterEquals, yytext);
            }
            YY_BREAK
        case 31: // rule src/Lexer/Lexer.l:61: "&&" :
            YY_USER_ACTION
#line 61 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::DoubleAmpersand, yytext);
            }
            YY_BREAK
        case 32: // rule src/Lexer/Lexer.l:62: "||" :
            YY_USER_ACTION
#line 62 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::DoublePipe, yytext);
            }
            YY_BREAK
        case 33: // rule src/Lexer/Lexer.l:63: "->" :
            YY_USER_ACTION
#line 63 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Arrow, yytext);
            }
            YY_BREAK
        case 34: // rule src/Lexer/Lexer.l:64: "::" :
            YY_USER_ACTION
#line 64 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Scope, yytext);
            }
            YY_BREAK
        case 35: // rule src/Lexer/Lexer.l:65: "++" :
            YY_USER_ACTION
#line 65 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Increment, yytext);
            }
            YY_BREAK
        case 36: // rule src/Lexer/Lexer.l:66: "--" :
            YY_USER_ACTION
#line 66 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Decrement, yytext);
            }
            YY_BREAK
        case 37: // rule src/Lexer/Lexer.l:67: "<<" :
            YY_USER_ACTION
#line 67 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::LShift, yytext);
            }
            YY_BREAK
        case 38: // rule src/Lexer/Lexer.l:68: ">>" :
            YY_USER_ACTION
#line 68 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::RShift, yytext);
            }

            YY_BREAK
        case 39: // rule src/Lexer/Lexer.l:71: "..." :
            YY_USER_ACTION
#line 71 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Ellipsis, yytext);
            }

            YY_BREAK
        case 40: // rule src/Lexer/Lexer.l:74: \"([^\"\\]|\\.)*\" :
            YY_USER_ACTION
#line 74 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::StringLiteral, yytext);
            }
            YY_BREAK
        case 41: // rule src/Lexer/Lexer.l:75: \'([^\'\\]|\\.)*\' :
            YY_USER_ACTION
#line 75 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::CharLiteral, yytext);
            }

            YY_BREAK
        case 42: // rule src/Lexer/Lexer.l:78: [0-9]+(\.[0-9]+) :
            YY_USER_ACTION
#line 78 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::FloatingLiteral, yytext);
            }
            YY_BREAK
        case 43: // rule src/Lexer/Lexer.l:79: [0-9]+ :
            YY_USER_ACTION
#line 79 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::IntegerLiteral, yytext);
            }

            YY_BREAK
        case 44: // rule src/Lexer/Lexer.l:88: [[:alpha:]_][[:alnum:]_]* :
            YY_USER_ACTION
#line 88 "src/Lexer/Lexer.l"
            {
                static std::unordered_map<std::string, TokenType> keywords = {
                    {"auto", TokenType::Auto},       {"struct", TokenType::Struct}, {"class", TokenType::Class},
                    {"union", TokenType::Union},     {"enum", TokenType::Enum},     {"namespace", TokenType::Namespace},
                    {"import", TokenType::Import},   {"as", TokenType::As},         {"if", TokenType::If},
                    {"else", TokenType::Else},       {"for", TokenType::For},       {"in", TokenType::In},
                    {"while", TokenType::While},     {"return", TokenType::Return}, {"label", TokenType::Label},
                    {"goto", TokenType::Goto},       {"case", TokenType::Case},     {"match", TokenType::Match},
                    {"true", TokenType::True},       {"false", TokenType::False},   {"public", TokenType::Public},
                    {"private", TokenType::Private}, {"string", TokenType::String}, {"char", TokenType::Char},
                    {"bool", TokenType::Bool},       {"void", TokenType::Void},     {"float", TokenType::Float},
                    {"double", TokenType::Double},   {"int64", TokenType::Int64},   {"int32", TokenType::Int32},
                    {"int16", TokenType::Int16},     {"int8", TokenType::Int8},     {"uint64", TokenType::UInt64},
                    {"uint32", TokenType::UInt32},   {"uint16", TokenType::UInt16}, {"uint8", TokenType::UInt8},
                    {"ptr", TokenType::Ptr}};

                std::string text = yytext;
                auto it = keywords.find(text);
                if (it != keywords.end())
                {
                    addToken(it->second, text);
                }
                else
                {
                    addToken(TokenType::Identifier, text);
                }
            }

            YY_BREAK
        case 45: // rule src/Lexer/Lexer.l:139: . :
            YY_USER_ACTION
#line 139 "src/Lexer/Lexer.l"
            {
                addToken(TokenType::Invalid, yytext);
            }
            YY_BREAK
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//  SECTION 3: user code                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#line 143 "src/Lexer/Lexer.l"

int main()
{
    yylex();
    for (auto &t : tokens)
    {
        // 输出：类型(枚举值) 词素 行 列
        std::cout << static_cast<int>(t.type) << " " << t.lexeme << " " << t.line << " " << t.column << std::endl;
    }
    return 0;
}
