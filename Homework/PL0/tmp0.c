#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

// #define DEBUG

#define KEYWORD_NUM 17
#define KEYWORD_MAX_LEN 12
#define NUMBER_MAX_LEN 12

enum symbol
{ // 符号表
    nul,
    ident,
    number,
    plus,
    minus,
    times,
    slash,
    oddsym,
    eql,
    neq,
    lss,
    leq,
    gtr,
    geq,
    lparen,
    rparen,
    comma,
    semicolon,
    period,
    becomes,
    beginsym,
    endsym,
    ifsym,
    thensym,
    whilesym,
    writesym,
    readsym,
    dosym,
    callsym,
    constsym,
    varsym,
    procsym,
    meida,
    name,
    name_,
    idnum
};

static enum symbol sym, wsym[KEYWORD_NUM], ssym[256];
static wchar_t word[KEYWORD_NUM][KEYWORD_MAX_LEN];
static wchar_t wch = 0;
static wchar_t id[KEYWORD_MAX_LEN] = {0};
static long long num = 0;

static FILE *src_file = NULL;

/**
 * 初始化
*/
static void init()
{
    for (int i = 0; i <= 255; i++)
        ssym[i] = nul;
    ssym['+'] = plus;
    ssym['-'] = minus;
    ssym['*'] = times;
    ssym['/'] = slash;
    ssym['('] = lparen;
    ssym[')'] = rparen;
    ssym['='] = eql;
    ssym[','] = comma;
    ssym['.'] = period;
    ssym['#'] = neq;
    ssym[';'] = semicolon;
    wcscpy(&(word[0][0]), L"begin");
    wcscpy(&(word[1][0]), L"call");
    wcscpy(&(word[2][0]), L"const");
    wcscpy(&(word[3][0]), L"do");
    wcscpy(&(word[4][0]), L"end");
    wcscpy(&(word[5][0]), L"if");
    wcscpy(&(word[6][0]), L"meida");
    wcscpy(&(word[7][0]), L"odd");
    wcscpy(&(word[8][0]), L"procedure");
    wcscpy(&(word[9][0]), L"read");
    wcscpy(&(word[10][0]), L"then");
    wcscpy(&(word[11][0]), L"var");
    wcscpy(&(word[12][0]), L"while");
    wcscpy(&(word[13][0]), L"write");
    wcscpy(&(word[14][0]), L"姓名");
    wcscpy(&(word[15][0]), L"学号");
    wcscpy(&(word[16][0]), L"荷西");
    wsym[0] = beginsym;
    wsym[1] = callsym;
    wsym[2] = constsym;
    wsym[3] = dosym;
    wsym[4] = endsym;
    wsym[5] = ifsym;
    wsym[6] = meida;
    wsym[7] = oddsym;
    wsym[8] = procsym;
    wsym[9] = readsym;
    wsym[10] = thensym;
    wsym[11] = varsym;
    wsym[12] = whilesym;
    wsym[13] = writesym;
    wsym[14] = name;
    wsym[15] = idnum;
    wsym[16] = name_;
}

/**
 * 获取一个字符
*/
static inline void getch(void)
{
    wch = fgetwc(src_file);
#ifdef DEBUG
    printf("---> %lc <---\n", wch == WEOF ? L'#' : wch);
#endif
}

static int getsym()
{
    wchar_t wstr[KEYWORD_MAX_LEN] = {0};
    int k = 0;

    /* 重置 num,id */
    num = 0;
    memset(id, 0, sizeof(id));

    /* 忽略空白符 */
    while (wch == L' ' || wch == L'\t' || wch == L'\n')
        getch();

    if (WEOF == wch)
    {
        printf("=>\terror\t无结束符\n");
        exit(-1);
    }

    if (iswalpha(wch) || (wch >= L'\u4e00' && wch <= L'\u9fa5'))
    { // 字母或汉字
        do
        {
            if (k < KEYWORD_MAX_LEN)
            {
                wstr[k++] = wch;
            }
            getch();
        } while (iswalpha(wch) || iswalnum(wch) || (wch >= L'\u4e00' && wch <= L'\u9fa5'));
        memcpy(id, wstr, --k);
        /* 折半查找保留字 */
        int i = 0, j = KEYWORD_NUM;
        do
        {
            k = (i + j) / 2;
            if (wcscmp(wstr, word[k]) <= 0)
                j = k - 1;
            if (wcscmp(wstr, word[k]) >= 0)
                i = k + 1;
#ifdef DEBUG
            printf("%d %d %d\n", k, i, j);
#endif
        } while (i <= j);
        if (i - 1 > j)
        {
            sym = wsym[k];
            printf("%d\t保留字\t%ls\n", sym, wstr);
        }
        else
        {
            sym = ident;
            printf("%d\t标识符\t%ls\n", sym, wstr);
        }
    }
    else if (iswdigit(wch))
    { // 数字
        sym = number;
        do
        {
            num = 10 * num + wch - L'0';
            k++;
            getch();
        } while (iswdigit(wch));
        if (--k > NUMBER_MAX_LEN)
            printf("=>\terror\t数字长度过大\n");
        printf("%d\t数字\t%lld\n", sym, num);
    }
    else if (wch >= 0 && wch < 256)
    { // ASCII字符
        if (wch == L':')
        {
            getch();
            if (wch == L'=')
            { // 处理 := 符
                sym = becomes;
                printf("%d\t运算符\t:=\n", sym);
                getch();
            }
            else
            {
                sym = nul;
                printf("%d\t无效符\t:\n", sym);
            }
        }
        else
        {
            if (wch == L'<')
            {
                getch();
                if (wch == L'=')
                { // 处理 <= 符
                    sym = leq;
                    printf("%d\t运算符\t<=\n", sym);
                    getch();
                }
                else
                {
                    sym = lss;
                    printf("%d\t运算符\t<\n", sym);
                    getch();
                }
            }
            else if (wch == L'>')
            {
                getch();
                if (wch == L'=')
                { // 处理 >= 符
                    sym = geq;
                    printf("%d\t运算符\t>=\n", sym);
                    getch();
                }
                else
                {
                    sym = gtr;
                    printf("%d\t运算符\t>\n", sym);
                    getch();
                }
            }
            else
            { // 其他单字符
                sym = ssym[wch];
#ifdef DEBUG
                printf("===>%d\n", sym);
#endif
                if (sym >= 3 && sym <= 8)
                    printf("%d\t运算符\t%lc\n", sym, wch);
                else if (sym == 0)
                    printf("%d\t无效符\t%lc\n", sym, wch);
                else
                    printf("%d\t界符\t%lc\n", sym, wch);
                if (sym != period)
                { // 处理结束符
                    getch();
                }
                else
                {
#ifdef DEBUG
                    printf("结束\n");
#endif
                    do {
                        getch();
                    } while (wch == L' ' || wch == L'\t' || wch == L'\n');
                    if (wch != WEOF) {
                        printf("=>\terror\t有多余字符\n");
                        exit(-1);
                    } else
                        exit(0);
                }
            }
        }
    }
    else
    { // 其他非法字符
        sym = nul;
        printf("%d\t无效符\t%lc\n", sym, wch);
        getch();
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int ret = 0;

    setlocale(LC_ALL, "zh_CN.UTF-8");

    /* 打开文件 */
    src_file = fopen("src.pl0", "r");
    if (!src_file)
    {
        printf("=>\terror\t打开文件失败\n");
        exit(-1);
    }

    init();

    getch();
    while (!getsym());
    return ret;
}