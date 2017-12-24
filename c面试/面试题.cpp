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