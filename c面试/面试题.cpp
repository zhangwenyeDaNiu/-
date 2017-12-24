//找错题

//试题1：
void test1()
{
　char string[10];
　char* str1 ="0123456789";
　strcpy( string, str1 );
}
//字符串str1需要11个字节才能存下（包括末尾‘\0’）
//而string只有10个字节，strcpy会导致数组越界

//试题2
void test2（）
{
	char string[10],str[10];
	int i;
	for(i=0;i<10;i++)
	{
		str1='a';
	}
	strcpy(string,str);
}
//错误的原因在与strcpy导致的越界访问
//百科中关于strcpy的解释
//原型声明：extern char *strcpy(char *dest,const char *src);
//头文件：string.h
//功能：把从src地址开始且含有NULL结束符的字符串赋值到以dest开始的地址空间
//说明：src和dest所指内存区域不可以重叠且dest必须有足够的空间来容纳src的字符串。
//返回指向dest的指针。
//简单地讲,就是第二的参数指针开始带'\0'结束的所有字符赋值给第一个参数指针开始的空间
//但是你这里根本没有'\0'的字符串结束标记,那就是会导致越界访问啊

//试题3
void test3(char* str1)
{
　char string[10];
　if( strlen( str1 ) <=10 )
　{
　　strcpy( string, str1 );
　}
}
//if(strlen(str1)<= 10)应改为if(strlen(str1) < 10)，
//因为strlen的结果未统计’\0’所占用的1个字节。

//试题4：
void GetMemory( char*p )
{
　p = (char*) malloc( 100 );
}

void Test( void ) 
{
　char*str = NULL;
　GetMemory( str ); 
　strcpy( str, "hello world" );
　printf( str );
}
//试题4传入中GetMemory(char *p )函数的形参为字符串指针，在函数内部修改形参并不能真正的改变传入形参的值，执行完
//char *str = NULL;
//GetMemory( str ); 后的str仍然为NULL；

//试题5：
char*GetMemory( void )
{ 
　char p[] ="hello world"; //malloc就能正常输出了
　return p; 
}

void Test( void )
{ 
　char*str = NULL; 
　str = GetMemory(); 
　printf( str ); //输出乱码
}
//char p[] = "hello world"; 
//return p; 
//的p[]数组为函数内的局部自动变量，在函数返回后，内存已经被释放。这是许多程序员常犯的错误，其根源在于不理解变量的生存期。

//试题6：
void GetMemory( char**p, int num )
{
　*p = (char*) malloc( num );
}

void Test( void )
{
　char*str = NULL;
　GetMemory( &str, 100 );
　strcpy( str, "hello" ); 
　printf( str ); 
}
//试题6的GetMemory避免了试题4的问题，传入GetMemory的参数为字符串指针的指针，但是在GetMemory中执行申请内存及赋值语句
//*p = (char *) malloc( num );
//后未判断内存是否申请成功，应加上：
//if ( *p == NULL )
//{
　	//进行申请内存失败处理
//}
//Test函数中也未对malloc的内存进行释放

//试题7：
void Test( void )
{
　char*str = (char*) malloc( 100 );
　strcpy( str, "hello" );
　free( str ); 
　... //省略的其它语句
}
//试题7存在与试题6同样的问题，在执行
//char *str = (char *) malloc(100);
//后未进行内存是否申请成功的判断；另外，在free(str)后未置str为空，导致可能变成一个“野”指针，应加上：
//str = NULL;

//试题8:
swap( int* p1,int* p2 )
{
　int*p;
　*p =*p1;
　*p1 =*p2;
　*p2 =*p;
}
//在swap函数中，p是一个“野”指针，有可能指向系统区，
//导致程序运行的崩溃。在VC++中DEBUG运行时提示错误“AccessViolation”。该程序应该改为：
swap( int* p1,int* p2 )
{
　int p;
　p =*p1;
　*p1 =*p2;
　*p2 = p;
}



//二.内功题
//试题1：分别给出BOOL，int，float，指针变量 与“零值”比较的 if 语句（假设变量名为var）
//解答：

//false为0
BOOL型变量：if(!var)
int型变量：if(var==0)

float型变量：
const float EPSINON = 0.00001;
if ((x >= - EPSINON) && (x <=EPSINON)

指针变量：　　if(var==NULL)
	
//剖析：
　　//考查对0值判断的“内功”，BOOL型变量的0判断完全可以写成if(var==0)，而int型变量也可以写成if(!var)，
    //指针变量的判断也可以写成if(!var)，上述写法虽然程序都能正确运行，但是未能清晰地表达程序的意思。 
　  //一般的，如果想让if判断一个变量的“真”、“假”，应直接使用if(var)、if(!var)，
    //表明其为“逻辑”判断；如果用if判断一个数值型变量(short、int、long等)，应该用if(var==0)，
	//表明是与0进行“数值”上的比较；而判断指针则适宜用if(var==NULL)，这是一种很好的编程习惯。
　　//浮点型变量并不精确，所以不可将float变量用“==”或“！=”与数字比较，应该设法转化成“>=”或“<=”形式。
    //如果写成if(x == 0.0)，则判为错，得0分。
	
	
//试题2：以下为WindowsNT下的32位C++程序，请计算sizeof的值
void Func ( char str[100] )
{
　sizeof( str ) =?
}
void*p = malloc( 100 );
sizeof ( p ) =?

//解答：
//sizeof( str ) = 4
//sizeof ( p ) = 4

//剖析：
　　//Func ( char str[100] )函数中数组名作为函数形参时，
	//在函数体内，数组名失去了本身的内涵，仅仅只是一个指针；
	//在失去其内涵的同时，它还失去了其常量特性，
	//可以作自增、自减等操作，可以被修改。
	
	//数组名的本质如下：
    //（1）数组名指代一种数据结构，这种数据结构就是数组；
	//例如：
	//char str[10];
	//cout << sizeof(str) << endl;
	//输出结果为10，str指代数据结构char[10]。
	
	//（2）数组名可以转换为指向其指代实体的指针，
	//而且是一个指针常量，不能作自增、自减等操作，不能被修改；
	//char str[10]; 
	//str++; //编译出错，提示str不是左值　
	
	//（3）数组名作为函数形参时，沦为普通指针。
	//Windows NT 32位平台下，指针的长度（占用内存的大小）为4字节，
	//故sizeof( str ) 、sizeof ( p) 都为4。

	
//试题3：写一个“标准”宏MIN，这个宏输入两个参数并返回较小的一个。
//另外，当你写下面的代码时会发生什么事？
least = MIN(*p++, b);

//解答：
#define MIN(A,B) ((A) <= (B) ? (A) : (B))
MIN(*p++, b)会产生宏的副作用

//剖析：
	//这个面试题主要考查面试者对宏定义的使用，
	//宏定义可以实现类似于函数的功能，
	//但是它终归不是函数，
	//而宏定义中括弧中的“参数”也不是真的参数，
	//在宏展开的时候对“参数”进行的是一对一的替换。
	
	//程序员对宏定义的使用要非常小心，特别要注意两个问题：
	//（1）谨慎地将宏定义中的“参数”和整个宏用用括弧括起来。
	//所以，严格地讲，下述解答：
	//#define MIN(A,B) (A) <= (B) ? (A) : (B)
	//#define MIN(A,B) (A <= B ? A : B )都应判0分；

	//（2）防止宏的副作用。
	//宏定义#define MIN(A,B) ((A) <= (B) ? (A) : (B))对MIN(*p++, b)的作用结果是：
	//((*p++) <= (b) ? (*p++) : (b))
	//这个表达式会产生副作用，指针p会作三次++自增操作。
	
	//除此之外，另一个应该判0分的解答是：
	//#define MIN(A,B) ((A) <= (B) ? (A) : (B)); 
	//这个解答在宏定义的后面加“;”，显示编写者对宏的概念模糊不清，只能被无情地判0分并被面试官淘汰。


//试题4：
// pStr是指向以'\0'结尾的字符串的指针
// steps是要求移动的n
void LoopMove ( char* pStr, int steps )
{
　// 请填充...
}

void LoopMove ( char* pStr, int steps )
{
	int len = strlen(pStr) - steps;
	char tmp[100];
	memcpy(tmp, pStr + steps, len);
	memcpy(pStr + len, pStr, steps);
	memcpy(pStr, tmp, len);
}

//试题7：编写类String的构造函数、析构函数和赋值函数，
//已知类String的原型为：

class String
{ 
　public: 
　　String(const char*str = NULL); // 普通构造函数 
　　String(const String &other); // 拷贝构造函数 
　　~ String(void); // 析构函数 
　　String & operator =(const String &other); // 赋值函数 
　private: 
　　char*m_data; // 用于保存字符串 
};

//解答：
//普通构造函数
　　String::string(const char*str)
	{
		if(str===NULL)
		{
			m_data[1]='\0';
		}
		else
		{
			int len=strlen(str);
			m_data=(char*)malloc(len+1);
			memcpy(m_data,str,len+1);
		}
	}
// 拷贝构造函数
	String(const String &other)
	{
		int len=strlen(other.m_data);
		m_data=(char*)malloc(len+1);
		memcpy(m_data,other.m_data,len+1);
	}
//赋值函数
	String & String::operator =(const String &other)
	{
		if(other==this)
		{
			return *this;
		}
		else
		{
			free(m_data);
			int len=strlen(other.m_data);
			m_data=(char*)malloc(len+1);
			memcpy(m_data,other.m_data,len+1);
			return *this;
		}
	}
	
	String::~ String(void)
	{
		free(m_data);
	}
//剖析：
//能够准确无误地编写出String类的构造函数、拷贝构造函数、
//赋值函数和析构函数的面试者至少已经具备了C++基本功的60%以上！
//在这个类中包括了指针类成员变量m_data，
//当类中包括指针类成员变量时，一定要重载其拷贝构造函数、
//赋值函数和析构函数，这既是对C++程序员的基本要求，
//也是《Effective　C++》中特别强调的条款。
//仔细学习这个类，特别注意加注释的得分点和加分点的意义，
//这样就具备了60%以上的C++基本功！

//试题8：请说出static和const关键字尽可能多的作用

//解答：
　　//static关键字至少有下列n个作用：
　　//（1）函数体内static变量的作用范围为该函数体，不同于auto变量，该变量的内存只被分配一次，因此其值在下次调用时仍维持上次的值；
　　//（2）在模块内的static全局变量可以被模块内所用函数访问，但不能被模块外其它函数访问；
　　//（3）在模块内的static函数只可被这一模块内的其它函数调用，这个函数的使用范围被限制在声明它的模块内；
　　//（4）在类中的static成员变量属于整个类所拥有，对类的所有对象只有一份拷贝；
　　//（5）在类中的static成员函数属于整个类所拥有，这个函数不接收this指针，因而只能访问类的static成员变量。

　　//const关键字至少有下列n个作用：
　　//（1）欲阻止一个变量被改变，可以使用const关键字。在定义该const变量时，通常需要对它进行初始化，因为以后就没有机会再去改变它了；
　　//（2）对指针来说，可以指定指针本身为const，也可以指定指针所指的数据为const，或二者同时指定为const；
　　//（3）在一个函数声明中，const可以修饰形参，表明它是一个输入参数，在函数内部不能改变其值；
　　//（4）对于类的成员函数，若指定其为const类型，则表明其是一个常函数，不能修改类的成员变量；
　　//（5）对于类的成员函数，有时候必须指定其返回值为const类型，以使得其返回值不为“左值”。例如：
const classA operator*(const classA& a1,const classA& a2);
　　operator*的返回结果必须是一个const对象。如果不是，这样的变态代码也不会编译出错：

classA a, b, c;
(a * b) = c; // 对a*b的结果赋值
　　操作(a * b) = c显然不符合编程者的初衷，也没有任何意义。

//剖析：
　//　惊讶吗？小小的static和const居然有这么多功能，我们能回答几个？如果只能回答1~2个，那还真得闭关再好好修炼修炼。

//　　这个题可以考查面试者对程序设计知识的掌握程度是初级、中级还是比较深入，没有一定的知识广度和深度，不可能对这个问题给出全面的解答。大多数人只能回答出static和const关键字的部分功能。











	