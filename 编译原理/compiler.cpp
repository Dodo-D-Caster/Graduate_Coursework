#include <iostream>
using namespace std;
char ch = ' ';   //������¶�����Դ�����ַ�
string strToken; //��Ź��ɵ��ʷ��ŵ��ַ���
string totalStr; //���������봮
int tmpStr = 0;  //��ǰ���봮ɨ�赽��λ��
string tmpID;    //�ݴ��ʶ������֮��������
bool isEnd = 0;  //�ж���ֹ
// bool IsDigit(char ch);

// //���� string����תint����
// int stringToInt(string s)
// {
//     int tmp = 0;
//     for(int i=0; i<s.length(); ++i)
//     {
//         if(IsDigit(s[i]))
//             tmp = tmp * 10 + s[i] - '0';
//         else
//             return -1;
//     }
//     return tmp;
// }

//���ʷ���
struct TOKEN
{
    int kind = 0;           //�����ֱ�-��������
    string attribute = "-"; //��������
};

//���ʷ��ű�
int rsNum = 0;    //�����ָ���
int opNum = 0;    //���������
int boNum = 0;    //�������
int idNum = 0;    //��ʶ������
int coNum = 0;    //��������
TOKEN rsWord[30]; //������
TOKEN opWord[30]; //�����
TOKEN boWord[30]; //���
TOKEN idWord[30]; //��ʶ��
TOKEN coWord[30]; //����
void initword()
{
    //������
    rsWord[rsNum].attribute = "int";
    rsWord[rsNum].kind = 5;
    rsNum++;
    rsWord[rsNum].attribute = "else";
    rsWord[rsNum].kind = 15;
    rsNum++;
    rsWord[rsNum].attribute = "if";
    rsWord[rsNum].kind = 17;
    rsNum++;
    rsWord[rsNum].attribute = "while";
    rsWord[rsNum].kind = 20;
    rsNum++;

    //�����
    opWord[opNum].attribute = "+";
    opWord[opNum].kind = 41;
    opNum++;
    opWord[opNum].attribute = "-";
    opWord[opNum].kind = 42;
    opNum++;
    opWord[opNum].attribute = "*";
    opWord[opNum].kind = 43;
    opNum++;
    opWord[opNum].attribute = "/";
    opWord[opNum].kind = 44;
    opNum++;
    opWord[opNum].attribute = "%";
    opWord[opNum].kind = 45;
    opNum++;
    opWord[opNum].attribute = "=";
    opWord[opNum].kind = 46;
    opNum++;
    opWord[opNum].attribute = ">";
    opWord[opNum].kind = 47;
    opNum++;
    opWord[opNum].attribute = ">=";
    opWord[opNum].kind = 48;
    opNum++;
    opWord[opNum].attribute = "<";
    opWord[opNum].kind = 49;
    opNum++;
    opWord[opNum].attribute = "<=";
    opWord[opNum].kind = 50;
    opNum++;
    opWord[opNum].attribute = "<=";
    opWord[opNum].kind = 50;
    opNum++;
    opWord[opNum].attribute = "==";
    opWord[opNum].kind = 51;
    opNum++;
    opWord[opNum].attribute = "!=";
    opWord[opNum].kind = 52;
    opNum++;
    opWord[opNum].attribute = "&&";
    opWord[opNum].kind = 53;
    opNum++;
    opWord[opNum].attribute = "||";
    opWord[opNum].kind = 54;
    opNum++;
    opWord[opNum].attribute = "!";
    opWord[opNum].kind = 55;
    opNum++;
    opWord[opNum].attribute = "++";
    opWord[opNum].kind = 56;
    opNum++;
    opWord[opNum].attribute = "--";
    opWord[opNum].kind = 57;
    opNum++;

    //���
    boWord[boNum].attribute = "(";
    boWord[boNum].kind = 81;
    boNum++;
    boWord[boNum].attribute = ")";
    boWord[boNum].kind = 82;
    boNum++;
    boWord[boNum].attribute = ";";
    boWord[boNum].kind = 84;
    boNum++;
    boWord[boNum].attribute = "{";
    boWord[boNum].kind = 86;
    boNum++;
    boWord[boNum].attribute = "}";
    boWord[boNum].kind = 87;
    boNum++;
    boWord[boNum].attribute = "[";
    boWord[boNum].kind = 88;
    boNum++;
    boWord[boNum].attribute = "]";
    boWord[boNum].kind = 89;
    boNum++;
    boWord[boNum].attribute = ",";
    boWord[boNum].kind = 90;
    boNum++;
}

//������봮����һ���ַ�,���û����Ϊ#
void GetChar()
{
    if (tmpStr < totalStr.length())
        ch = totalStr[tmpStr++];
    else
        ch = '#';
}

//��������Ƿ�Ϊ�հף��������getCharֱ���ǿհ�
void GetBC()
{
    while (ch == ' ')
        GetChar();
}

//��ch�е��ַ����ӵ�strToken֮��
void Concat()
{
    strToken += ch;
    ch = ' ';
}

//��strToken���ұ����ֱ����Ǳ������򷵻ر��룬���򷵻�0ֵ
int Reserve()
{
    for (int i = 0; i < rsNum; ++i)
        if (strToken == rsWord[i].attribute)
            return rsWord[i].kind;
    return 0;
}

//������ָʾ���ص�һ��λ�ã���ch��Ϊ�հ׷�
void Retract()
{
    tmpStr--;
    ch = ' ';
}

//�ж��Ƿ�Ϊ��ĸ
bool IsLetter(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return true;
    else
        return false;
}

//�ж��Ƿ�Ϊ����
bool IsDigit(char ch)
{
    if (ch >= '0' && ch <= '9')
        return true;
    else
        return false;
}

//�ж��Ƿ�Ϊ�����,���������Ϊ1~2λ,����λ��
int IsOp(char ch)
{
    //�ȼ�鳤��Ϊ2��
    for (int i = 0; i < opNum; ++i)
        if (opWord[i].attribute.length() == 2 && ch == opWord[i].attribute[0] && totalStr[tmpStr] == opWord[i].attribute[1])
        {
            return i;
        }
    //�ټ�鳤��Ϊ1��
    for (int i = 0; i < opNum; ++i)
        if (opWord[i].attribute.length() == 1 && ch == opWord[i].attribute[0])
            return i;
    return -1;
}

//�ж��Ƿ�Ϊ���,���Ϊ1λ,����λ��
int IsBo(char ch)
{
    for (int i = 0; i < boNum; ++i)
        if (ch == boWord[i].attribute[0])
            return i;
    return -1;
}

//��strToken�еı�ʶ�������ʶ���������ظñ�ʶ����TOKEN
TOKEN InsertId(string str)
{
    idWord[idNum].kind = 111;
    idWord[idNum].attribute = str;
    return idWord[idNum++];
}

//��strToken���볣�������ظó�����TOKEN
TOKEN InsertConst(string str)
{
    coWord[coNum].kind = 100;
    // coWord[coNum].attribute = str;
    if(tmpID != "")
        coWord[coNum].attribute = tmpID;
    else
        coWord[coNum].attribute = str;
    return coWord[coNum++];
}

//�ʷ�����
TOKEN myLexer()
{
    TOKEN tmp; //����ֵ
    int code;  //�ֱ����
    strToken = "";
    GetChar(); //��ȡ��һ���ַ�
    GetBC();   //�����ո�
    //��������ʱ��tmp��kindֵΪ0
    if (ch == '#')
        return tmp;
    //Ϊ��ʶ��������
    else if (IsLetter(ch))
    {
        while (IsLetter(ch) || IsDigit(ch))
        {
            Concat();
            GetChar();
        }
        if (ch != '#')
            Retract();
        code = Reserve();
        //Ϊ��ʶ��
        if (code == 0)
        {
            tmp = InsertId(strToken);
            tmpID = strToken;
            strToken.clear();
            return tmp;
        }
        //Ϊ������
        else
        {
            tmp.kind = code;
            tmp.attribute = "-";
            strToken.clear();
            return tmp;
        }
    }
    //Ϊ����
    else if (IsDigit(ch))
    {
        while (IsDigit(ch))
        {
            Concat();
            GetChar();
        }
        if (ch != '#')
            Retract();
        //�ж��Ƿ��� a = num1 + num2�ȵ��������
        GetChar();
        GetBC();
        if(IsOp(ch) != -1)
            tmpID = "";
        tmpStr--;   // ����
        tmp = InsertConst(strToken);
        strToken.clear();
        // tmp.isNum = 1;
        return tmp;
    }
    //Ϊ�����
    else if (IsOp(ch) != -1)
    {
        tmp = opWord[IsOp(ch)];
        if (tmp.attribute.length() == 2)
            GetChar();
        tmp.attribute = "-";
        return tmp;
    }
    //Ϊ���
    else if (IsBo(ch) != -1)
    {
        tmp = boWord[IsBo(ch)];
        tmp.attribute = "-";
        return tmp;
    }
    //��������ų�����ʱ���ص�tmp��kindΪ0
    else
    {
        tmp.kind = 0;
        tmp.attribute = "-";
        return tmp;
    }
}

string out4YS[100][4];  //���������� ��Ԫʽ
int outList[100];       //���������Ԫʽ������
void initOutList()
{
    for(int i=0; i<100; ++i)
        outList[i] = -1;
}

int nOut = 0;   //��ǰ���λ��
int nextquad = 0;   //ָ����һ����Ҫ��������Ԫʽ��ַ
// �����ɵ���Ԫʽ��䷢�͵�����ļ���
void emit(string op, string a, string b, string tmp)
{
    nextquad++;
    // cout<<countEmit++<<": "<<op<<","<<a<<","<<b<<","<<tmp<<endl;
    out4YS[nOut][0] = op;
    out4YS[nOut][1] = a;
    out4YS[nOut][2] = b;
    out4YS[nOut][3] = tmp;
    outList[nOut] = nOut;
    nOut++;
}

int countEmit = 0;
int startOut = 0;
void output4YS()
{
    for(int i=startOut; i<nOut; ++i)
        cout<<countEmit++<<": "<<out4YS[i][0]<<","<<out4YS[i][1]<<","<<out4YS[i][2]<<","<<out4YS[i][3]<<endl;
}

// �ķ���������
struct X
{
    string place = "";      //��������
    string inArray = "";    //��������
    int inNdim = 0;         //�±���ʽ������ά��
    string inPlace = "";    //��Elist�е��±���ʽ���������ֵ
    string array = "";      //ָ����ű�����Ӧ�������ֱ����ָ��
    string offset = "";     //XΪ�����֣�ΪNULL��XΪ�������֣�Ϊ�����ַ�б�������
    int truelist = -1;      //����
    int falselist = -1;
    int inTruelist = -1;
    int inFalselist = -1;
    int nextlist = -1;  //ָ����һ����Ԫʽ
    int inNextlist = -1;
};


// ����һ������i�����б�
int makelist(int i)
{
    return i;
}

// ����p1��p2Ϊ���׵��������ϲ�Ϊһ���� p2 ����β�ĵ� 4 ���θ�Ϊ p1���ϲ��������Ϊ p1�����ͺϲ��������
int merge(int p1, int p2)
{
    out4YS[p1][3] = to_string(p2);
    for(int i=0; i<nOut; ++i)
    {
        if(out4YS[i][3].find('T') == 0)
            continue;
        if(outList[i] == p1)
        {
            out4YS[i][3] = to_string(p2);
            outList[i] = p2;
        }
    }
    return p2;
}

bool flag[100] = {0};
// ���� ��p�����ӵ�ÿ����Ԫʽ�ĵ��ĸ�����������Ϊt
void backpatch(int p, int t)
{
    if(p != -1)
        for(int i=0; i<nOut; ++i)
        {
            if(outList[i] == p && flag[i]==0)
            {
                out4YS[i][3] = to_string(t);
                outList[i] = t;
                flag[i] = 1;
            }
        }
}

//����nj����array����ĵ�jά����
string limit(string array, int j){
    return array + to_string(j);
}

TOKEN SYM; //�Ӵʷ����������õĵ��ʷ���
X expr();
X term();
X rest5(X rest5_);
X rest6(X rest6_);
X unary();
X factor();
X bool_();
X equality();
X rest4(X rest4_);
X rel();
X rop_expr(X rop_expr_);
X stmts();
X rest0(X rest0_);
X stmt();
X loc();
X resta(X resta_);
X elist(X elist_);
X rest1(X rest1_);

int M()
{
    return nextquad;
}

int N()
{
    int n = makelist(nextquad);
    emit("j","-","-","0");
    return n;
}

// X exprTmp,termTmp,rest5Tmp,rest6Tmp,unaryTmp,factorTmp,stmtTmp,locTmp,restaTmp;

// ����һ����ʱ���������֣���t1
int countTemp = 1;
string newtemp()
{
    return "T" + to_string(countTemp++);
}

// ���ôʷ�������
void advance()
{
    SYM = myLexer();
    while(SYM.kind == 0 && ch != '#')
        SYM = myLexer();
}

X term()
{
    X termTmp, unaryTmp, rest6Tmp;
    // cout<<"term -> unary rest6"<<endl;
    unaryTmp = unary();
    rest6Tmp.inArray = unaryTmp.place;
    rest6Tmp = rest6(rest6Tmp);
    ////////////////
    if(rest6Tmp.place == "")
        rest6Tmp.place = rest6Tmp.inArray;  //ͬrest5
    termTmp.place = rest6Tmp.place;
    return termTmp;
}

X rest6(X rest6_)
{
    // * 43
    if(SYM.kind == 43)
    {
        // cout<<111<<endl;
        X rest6Tmp, unaryTmp, rest61Tmp;
        advance();
        // cout<<"rest6 -> * unary rest6"<<endl;
        unaryTmp = unary();
        rest61Tmp.inArray = newtemp();
        emit("*",rest6_.inArray,unaryTmp.place,rest61Tmp.inArray);
        rest6Tmp = rest6(rest61Tmp);
        rest6Tmp.place = rest61Tmp.place;
        return rest6Tmp;
    }
    // / 44
    else if(SYM.kind == 44)
    {
        X rest6Tmp, unaryTmp, rest61Tmp;
        advance();
        // cout<<"rest6 -> / unary rest6"<<endl;
        unaryTmp = unary();
        rest61Tmp.inArray = newtemp();
        emit("/",rest6_.inArray,unaryTmp.place,rest61Tmp.inArray);
        rest6Tmp = rest6(rest61Tmp);
        rest6Tmp.place = rest61Tmp.place;
        return rest6Tmp;
    }
    else
    {
        rest6_.place = rest6_.inArray;
        return rest6_;
    }
}

X unary()
{
    X unaryTmp, factorTmp;
    // cout<<"unary -> factor"<<endl;
    factorTmp = factor();
    unaryTmp.place = factorTmp.place;
    return unaryTmp;
}

X factor()
{
    if(SYM.kind == 100)
    {
        X factorTmp;
        // cout<<"factor -> num"<<endl;
        factorTmp.place = SYM.attribute;    //factor.place = num.value
        advance();
        return factorTmp;
    }
    // ( 81
    else if(SYM.kind == 81)
    {
        X factorTmp, exprTmp;
        advance();
        exprTmp = expr();
        // ) 82
        if(SYM.kind == 82)
        {
            // cout<<"factor -> (expr)"<<endl;
            factorTmp.place = exprTmp.place;    //
            advance();
            return factorTmp;
        }
        else
        {
            cout<<"ERROR_factor_NO_)"<<endl;
            exit(0);
        }
    }
    else
    {
        X factorTmp, locTmp;
        // cout<<"factor -> loc"<<endl;
        locTmp = loc();
        if(locTmp.offset == "")
            factorTmp.place = locTmp.place;
        else
        {
            factorTmp.place = newtemp();
            emit("=[]",locTmp.place+"["+locTmp.offset+"]","-",factorTmp.place);
        }
        return factorTmp;
    }
}

X expr()
{
    // cout<<"expr -> term rest5"<<endl;
    X rest5Tmp, termTmp, exprTmp;
    termTmp = term();
    rest5Tmp.inArray = termTmp.place;
    rest5Tmp = rest5(rest5Tmp);
    // cout<<rest5Tmp.inArray<<endl;
    //------------------------------------------
    if(rest5Tmp.place == "")
        rest5Tmp.place = rest5Tmp.inArray;  //�����ֵ����
    exprTmp.place = rest5Tmp.place;
    return exprTmp;
}

X rest5(X rest5_)
{
    // cout<<rest5_.inArray<<endl;
    // + 41
    if(SYM.kind == 41)
    {
        X rest5Tmp, rest51Tmp,termTmp;
        advance();
        // cout<<"rest5 -> + term rest5"<<endl;
        termTmp = term();
        rest51Tmp.inArray = newtemp();
        emit("+",rest5_.inArray,termTmp.place,rest51Tmp.inArray);
        rest5Tmp = rest5(rest51Tmp);
        rest5Tmp.place = rest51Tmp.place;
        return rest5Tmp;
    }
    // - 42
    else if(SYM.kind == 42)
    {
        X rest5Tmp, rest51Tmp,termTmp;
        advance();
        // cout<<"rest5 -> - term rest5"<<endl;
        termTmp = term();
        rest51Tmp.inArray = newtemp();
        emit("-",rest5_.inArray,termTmp.place,rest51Tmp.inArray);
        rest5Tmp = rest5(rest51Tmp);
        rest5Tmp.place = rest51Tmp.place;
        return rest5Tmp;
    }
    else
    {
        // cout<<"rest5 -> ��"<<endl;
        rest5_.place = rest5_.inArray;
        return rest5_;
    }
}

X bool_()
{
    // cout<<"bool -> quality"<<endl;
    X boolTmp, equalityTmp;
    equalityTmp = equality();
    boolTmp.truelist = equalityTmp.truelist;
    boolTmp.falselist = equalityTmp.falselist;
    return boolTmp;
}

X equality()
{
    // cout<<"equality -> rel rest4"<<endl;
    X rest4Tmp, relTmp, equalityTmp;
    relTmp = rel();
    rest4Tmp.inTruelist = relTmp.truelist;
    rest4Tmp.inFalselist = relTmp.falselist;
    rest4Tmp = rest4(rest4Tmp);
    equalityTmp.truelist = rest4Tmp.truelist;
    equalityTmp.falselist = rest4Tmp.falselist;
    return equalityTmp;
}

X rest4(X rest4_)
{
    X rest4Tmp;
    // == 51
    if(SYM.kind == 51)
    {
        advance();
        cout<<"rest4 -> == rel rest4"<<endl;
        rel();
        rest4(rest4Tmp);
        return rest4Tmp;
    }
    // != 52
    else if(SYM.kind == 52)
    {
        advance();
        cout<<"rest4 -> != rel rest4"<<endl;
        rel();
        rest4(rest4Tmp);
        return rest4Tmp;
    }
    else
    {
        // cout<<"rest4 -> ��"<<endl;
        rest4_.truelist = rest4_.inTruelist;
        rest4_.falselist = rest4_.inFalselist;
        return rest4_;
    }
}

X rel()
{
    // cout<<"rel -> expr rop_expr"<<endl;
    X exprTmp, rop_exprTmp, relTmp;
    exprTmp = expr();
    rop_exprTmp.inPlace = exprTmp.place;
    rop_exprTmp = rop_expr(rop_exprTmp);
    relTmp.truelist = rop_exprTmp.truelist;
    relTmp.falselist = rop_exprTmp.falselist;
    return relTmp;
}

X rop_expr(X rop_expr_)
{
    X exprTmp;
    // < 49
    if(SYM.kind == 49)
    {
        advance();
        // cout<<"rop_expr -> < expr"<<endl;
        exprTmp = expr();
        rop_expr_.truelist = makelist(nextquad);
        rop_expr_.falselist = makelist(nextquad+1);
        emit("j<",rop_expr_.inPlace,exprTmp.place,"-");
        emit("j","-","-","-");
        return rop_expr_;
    }
    // <= 50
    else if(SYM.kind == 50)
    {
        advance();
        // cout<<"rop_expr -> <= expr"<<endl;
        exprTmp = expr();
        rop_expr_.truelist = makelist(nextquad);
        rop_expr_.falselist = makelist(nextquad+1);
        emit("j<=",rop_expr_.inPlace,exprTmp.place,"-");
        emit("j","-","-","-");
        return rop_expr_;
    }
    // > 47
    else if(SYM.kind == 47)
    {
        advance();
        // cout<<"rop_expr -> > expr"<<endl;
        exprTmp = expr();
        rop_expr_.truelist = makelist(nextquad);
        rop_expr_.falselist = makelist(nextquad+1);
        emit("j>",rop_expr_.inPlace,exprTmp.place,"-");
        emit("j","-","-","-");
        return rop_expr_;
    }
    // >= 48
    else if(SYM.kind == 48)
    {
        advance();
        // cout<<"rop_expr -> >= expr"<<endl;
        exprTmp = expr();
        rop_expr_.truelist = makelist(nextquad);
        rop_expr_.falselist = makelist(nextquad+1);
        emit("j>=",rop_expr_.inPlace,exprTmp.place,"-");
        emit("j","-","-","-");
        return rop_expr_;
    }
    else
    {
        // cout<<"rop_expr -> ��"<<endl;
        rop_expr_.truelist = makelist(nextquad);
        rop_expr_.falselist = makelist(nextquad+1);
        emit("jnz",rop_expr_.inPlace,"-","-");
        emit("j","-","-","-");
        return rop_expr_;
    }
}

X stmts()
{
    // cout<<"stmts -> stmt rest0"<<endl;
    X rest0Tmp, stmtTmp, stmtsTmp;
    stmtTmp = stmt();
    rest0Tmp.inNextlist = stmtTmp.nextlist;
    rest0Tmp = rest0(rest0Tmp);
    stmtsTmp.nextlist = rest0Tmp.nextlist;
    return stmtsTmp;
}

X rest0(X rest0_)
{
    // ; 84
    // if(SYM.kind != 84)
    if(SYM.kind==111 || SYM.kind==17 || SYM.kind == 20)
    {
        // cout<<111<<endl;
        // cout<<"rest0 -> stmt rest0"<<endl;
        X stmtTmp, rest0Tmp;
        int m = M();
        stmtTmp = stmt();
        backpatch(rest0_.inNextlist,m);
        rest0Tmp.inNextlist = stmtTmp.nextlist;
        rest0Tmp = rest0(rest0Tmp);
        rest0_.nextlist = rest0_.inNextlist;
        return rest0_;
    }
    else
    {
        // cout<<"rest0 -> ��"<<endl;
        advance();
        rest0_.nextlist = rest0_.inNextlist;
        isEnd = 1;
        return rest0_;
    }
}

int m3;
int boolFALSE;
X stmt()
{
    // if 17
    if(SYM.kind == 17)
    {
        X boolTmp, stmt1Tmp, stmt2Tmp;
        int m1, m2, n;
        int m0 = M();
        advance();
        // ( 81
        if(SYM.kind == 81)
        {
            advance();
            boolTmp = bool_();
            // ) 82
            if(SYM.kind == 82)
            {
                advance();
                m1 = M();
                stmt1Tmp = stmt();
                n = N();
                // ; 84
                if(SYM.kind == 84)
                    advance();
                // else 15
                if(SYM.kind == 15)
                {
                    // cout<<"stmt -> if(bool) stmt else stmt"<<endl;
                    advance();
                    m2 = M();
                    stmt2Tmp = stmt();
                    stmt2Tmp.nextlist = merge(merge(stmt1Tmp.nextlist,n),stmt2Tmp.nextlist);
                    backpatch(boolTmp.truelist,m1);
                    backpatch(boolTmp.falselist,m2);
                    return stmt2Tmp;
                }
                else
                {
                    cout<<"ERROR_stmt_if_NO_else"<<endl;
                    exit(0);
                }
            }
            else
            {
                cout<<"ERROR_stmt_if_NO_)"<<endl;
                exit(0);
            }
        }
        else
        {
            cout<<"ERROR_stmt_if_NO_("<<endl;
            exit(0);
        }
    }
    //while 20
    else if(SYM.kind == 20)
    {
        X boolTmp, stmtTmp;
        int m1,m2;
        advance();
        // ( 81
        if(SYM.kind == 81)
        {
            advance();
            m1 = M();
            // cout<<m1<<endl;
            boolTmp = bool_();
            // ) 82
            if(SYM.kind == 82)
            {
                // cout<<"stmt -> while(bool) stmt"<<endl;
                advance();
                m2 = M();
                stmtTmp = stmt();
                m3 = M()+1;
                boolFALSE = boolTmp.falselist;
                backpatch(stmtTmp.nextlist,m1);
                backpatch(boolTmp.truelist,m2);
                stmtTmp.nextlist = boolTmp.falselist;
                emit("j","-","-",to_string(m1));
                return stmtTmp;
            }
            else
            {
                cout<<"ERROR_stmt_while_NO_)"<<endl;
                exit(0);
            }
        }
        else
        {
            cout<<"ERROR_stmt_while_NO_("<<endl;
            exit(0);
        }
    }
    else
    {
        X exprTmp,locTmp,stmtTmp;
        locTmp = loc();
        // = 46
        if(SYM.kind == 46)
        {
            // cout<<"stmt -> loc = expr"<<endl;
            advance();
            exprTmp = expr();
            if(locTmp.offset == "")
                emit("=",exprTmp.place,"-",locTmp.place);
            else
                emit("[]=",exprTmp.place,"-",locTmp.place+"["+locTmp.offset+"]");
            stmtTmp.nextlist = makelist(nextquad);/////
            return stmtTmp;
        }
        else
        {
            cout<<"ERROR_stmt_NO_="<<endl;
            exit(0);
        }
    }
}

X loc()
{
    X restaTmp, locTmp;
    // cout<<"loc -> id resta"<<endl;
    string id = SYM.attribute;
    restaTmp.inArray = id;
    advance();
    restaTmp = resta(restaTmp);
    locTmp.place = restaTmp.place;
    locTmp.offset = restaTmp.offset;
    return locTmp;
}

X resta(X resta_)
{
    // [ 88
    if(SYM.kind == 88)
    {
        X elistTmp, restaTmp;
        // elistTmp.inArray = resta_.inArray;
        advance();
        elistTmp = elist(elistTmp);
        // ] 89
        if(SYM.kind == 89)
        {
            elistTmp.inArray = resta_.inArray;
            // cout<<"resta -> [elist]"<<endl;
            advance();
            restaTmp.place = newtemp();
            emit("-",elistTmp.inArray,"C",restaTmp.place);
            restaTmp.offset = newtemp();
            emit("*","w",elistTmp.offset,restaTmp.offset);
            return restaTmp;
        }
        else
        {
            cout<<"ERROR_resta_NO_]"<<endl;
            exit(0);
        }
    }
    else
    {
        // cout<<"resta -> ��"<<endl;
        resta_.place = resta_.inArray;
        resta_.offset = "";
        return resta_;
    }
}

X elist(X elist_)
{
    X exprTmp, elistTmp, rest1Tmp;
    // cout<<"elist -> expr rest1"<<endl;
    exprTmp = expr();
    rest1Tmp.inArray = elist_.inArray;
    rest1Tmp.inNdim = 1;
    rest1Tmp.inPlace = exprTmp.place;
    rest1Tmp = rest1(rest1Tmp);
    elistTmp.array = rest1Tmp.array;
    elistTmp.offset = rest1Tmp.offset;
    return elistTmp;
}

X rest1(X rest1_)
{
    // , 90
    if(SYM.kind == 90)
    {
        X exprTmp, rest1Tmp;
        advance();
        // cout<<"rest1 -> , expr rest1"<<endl;
        exprTmp = expr();
        string t = newtemp();
        int m = rest1_.inNdim + 1;
        emit("*",rest1_.inPlace,limit(rest1_.inArray,m),t);
        emit("+",t,exprTmp.place,t);
        rest1Tmp.inArray = rest1_.inArray;
        rest1Tmp.inNdim = m;
        rest1Tmp.inPlace = t;
        rest1Tmp = rest1(rest1Tmp);
        rest1_.array = rest1Tmp.array;
        rest1_.offset = rest1Tmp.offset;
        // return rest1_;
        return rest1Tmp;
    }
    else
    {
        // cout<<"rest1 -> ��"<<endl;
        rest1_.array = rest1_.inArray;
        rest1_.offset = rest1_.inPlace;
        return rest1_;
    }
}

int main()
{
    initword();
    initOutList();

    // // �ʷ�����
    // while (getline(cin, totalStr))
    // {
    //     while (ch != '#')
    //     {
    //         TOKEN token = myLexer();
    //         if (token.kind != 0)
    //             cout << "(" << token.kind << "," << token.attribute << ")" << endl;
    //     }
    //     ch = ' ';
    //     tmpStr = 0;
    // }
    
    // // �﷨����
    // string str;
    // while(getline(cin, str))
    //     totalStr += ' ' + str;
    // advance();
    // while(isEnd == 0)
    // {
    //     stmts();
    //     if(SYM.kind != 0)
    //     {
    //         isEnd = 0;
    //     }
    // }

    // �������
    string str;
    while(getline(cin, str))
        totalStr += ' ' + str;
    advance();
    bool while_first = 0;
    while(isEnd==0)
    {
        if(SYM.kind == 20)
            while_first = 1;
        stmts();
        if(while_first == 1)
            backpatch(boolFALSE, m3);
        output4YS();
        if(SYM.kind != 0)
        {
            isEnd = 0;
            startOut = nOut;
        }
    }
    return 0;
}
