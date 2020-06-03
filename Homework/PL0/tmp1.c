#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#define KEYWORD_NUM 17
#define KEYWORD_MAX_LEN 12
#define NUMBER_MAX_LEN 12

// 符号表
enum symbol {
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

//使用结构体装分析结果
struct item{
    int num;
    wchar_t symname[32];
    struct item* next;
} result,*lastitem = &result;

static enum symbol sym, wsym[KEYWORD_NUM], ssym[256];
static wchar_t word[KEYWORD_NUM][KEYWORD_MAX_LEN];
static wchar_t wch = 0;
static wchar_t id[KEYWORD_MAX_LEN] = {0};
static long long num = 0;
wchar_t line[80] = {0};

static FILE *file = NULL;

//将结果加入结果链表中
void additem(struct item* tmp,int num,wchar_t sysname[]){
    lastitem  = malloc(sizeof(struct item));
    lastitem->num = num;
    wcscpy(lastitem->symname,sysname);
    lastitem->next = NULL;
    tmp->next = lastitem;
}

// 初始化数据
static void init() {
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

// 获取一个字符
void getch(void) {
    static int ptr = 0, end = 0;
    if (ptr == end) //保证读完一行再读下一行
    {
        end = 0; //重置ch的位置ptr和tmp值
        ptr = 0;
        wch = L' ';
        while (wch != 10) //读入一行
        {
            if ((wch = fgetwc(file)) == WEOF) {
                line[end] = WEOF;
                break;
            }
            line[end] = wch;
            end++;
        }
    }
    wch = line[ptr]; //一个一个的读当前行
    ptr++;
}

//词法分析
static int getsym() {
    wchar_t wstr[KEYWORD_MAX_LEN] = {0};
    int k = 0;

    // 重置 num,id
    num = 0;
    memset(id, 0, sizeof(id));

    // 忽略空格、tab、回车
    while (wch == L' ' || wch == L'\t' || wch == L'\n')
        getch();
    if (wch == WEOF || sym == period) {
        puts("==>\t已读完");
        return 1;
    }
    // 是字母或汉字
    if (iswalpha(wch) || (wch >= L'\u4e00' && wch <= L'\u9fa5')) {
        do {
            if (k < KEYWORD_MAX_LEN) {
                wstr[k++] = wch;
            }
            getch();
        } while (iswalpha(wch) || iswalnum(wch) ||
                 (wch >= L'\u4e00' && wch <= L'\u9fa5'));
        memcpy(id, wstr, --k);
        // 折半查找保留字
        int i = 0, j = KEYWORD_NUM;
        do {
            k = (i + j) / 2;
            if (wcscmp(wstr, word[k]) <= 0)
                j = k - 1;
            if (wcscmp(wstr, word[k]) >= 0)
                i = k + 1;
        } while (i <= j);
        if (i - 1 > j) {
            sym = wsym[k];
            additem(lastitem,sym,wstr); //将当前分析结果添加到结果链表中
            printf("%ls\t保留字\n", wstr);
        } else {
            sym = ident;
            additem(lastitem, sym, wstr); //将当前分析结果添加到结果链表中
            printf("%ls\t标识符\n", wstr);
        }
    } else if (iswdigit(wch)) { // 是数字
        sym = number;
        wchar_t numstring[KEYWORD_MAX_LEN] = {0};//存储数字的string
        do {
            num = 10 * num + wch - L'0';
            numstring[k] = wch;
            k++;
            getch();
        } while (iswdigit(wch));
        if (--k > NUMBER_MAX_LEN)
            printf("=>\terror\t数字过长\n");
        additem(lastitem, sym, numstring); //将当前分析结果添加到结果链表中
        printf("%lld\t数字\n", num);
    } else if (wch >= 0 && wch < 256) { // 处理符号
        // 处理 := 符
        if (wch == L':') {
            getch();
            if (wch == L'=') {
                sym = becomes;
                additem(lastitem, sym, L":="); //将当前分析结果添加到结果链表中
                printf(":=\t运算符\n");
                getch();
            } else {
                sym = nul;
                additem(lastitem, sym, L"");
                printf(":\t无效符\n");
            }
        } else {
            // 处理 <= 符
            if (wch == L'<') {
                getch();
                if (wch == L'=') {
                    sym = leq;
                    additem(lastitem, sym, L"<=");
                    printf("<=\t运算符\n");
                    getch();
                } else {
                    sym = lss;
                    additem(lastitem, sym, L"<");
                    printf("<\t运算符\n");
                    getch();
                }
            } else if (wch == L'>') {
                // 处理 >= 符
                getch();
                if (wch == L'=') {
                    sym = geq;
                    additem(lastitem, sym, L">=");
                    printf(">=\t运算符\n");
                    getch();
                } else {
                    sym = gtr;
                    additem(lastitem, sym, L">");
                    printf(">\t运算符\n");
                    getch();
                }
            } else { // 其他单字符
                sym = ssym[wch];
                wchar_t tmp[2] = {0};
                tmp[0] = wch;
                additem(lastitem, sym, tmp);
                if (sym >= 3 && sym <= 8)
                    printf("%lc\t运算符\n", wch);
                else if (sym == 0)
                    printf("%lc\t无效符\n", wch);
                else
                    printf("%lc\t界符\n", wch);
                getch();
            }
        }
    } else { // 处理非法字符
        sym = nul;
        wchar_t tmp[2] = {0};
        tmp[0] = wch;
        additem(lastitem, sym, tmp);
        printf("%lc\t无效符\n", wch);
        getch();
    }
    return 0;
}

int main() {
    // 设置地域化信息以支持中文
    setlocale(LC_ALL, "zh_CN.UTF-8");
    // 读取文件
    file = fopen("src.pl0", "r");
    if (!file) {
        printf("=>\terror\t读取文件失败\n");
        exit(-1);
    }
    // 初始化数据
    init();
    getch();
    while (!getsym())
        // 当前字符的分析结果存入lastitem中可作为接口调用
        // printf("%d\t%ls\n", lastitem->num,lastitem->symname);
        ;
    return 0;
}