#include"wfunction.h"
#include<list>
#include<string>
#include<Windows.h>

using namespace std;
namespace io = boost::iostreams;
std::string wfunction::itos(long i) 
{
	std::ostringstream os; 
	os<<i; 
	std::string result;  
	std::istringstream is(os.str()); 
	is>>result;
	return result; 
}

std::string wfunction::ftos(double f)
{
	std::ostringstream os; 
	os<<f; 
	std::string result;  
	std::istringstream is(os.str()); 
	is>>result;
	return result; 
}

list<string> wfunction::splitstring(std::string tp)
{
	return splitstring(tp,",");
}

list<string> wfunction::splitstring(std::string tp,const std::string & splitchar)
{
	list<string> ret;
	while(tp.size())
	{		
		int index=tp.find_first_of(splitchar);

		string tmpstring=tp.substr(0,index);
		ret.push_back(tmpstring);

		if(index==-1)
		{
			break;
		}
		tp=tp.substr(index+1);
	}
	return ret;
}

char * wfunction::utf82gbk(const char * strUtf8)
{
       int len=MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8, -1, NULL,0); 
       unsigned short * wszGBK = new unsigned short[len+1];       
       memset(wszGBK, 0, len * 2 + 2); 
       MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUtf8, -1, (LPWSTR)wszGBK, len);
       len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
       char *szGBK=new char[len + 1]; 
       memset(szGBK, 0, len + 1); 
       WideCharToMultiByte (CP_ACP, 0, (LPCWSTR)wszGBK, -1, (LPSTR)szGBK, len, NULL,NULL);
       return szGBK; 
}

char * wfunction::gbk2utf8(const char * strGBK)
{ 
       int len=MultiByteToWideChar(CP_ACP,0,(LPCSTR)strGBK, -1, NULL,0); 
       unsigned short * wszUtf8 = new unsigned short[len+1]; 
       memset(wszUtf8, 0, len * 2 + 2); 
       MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strGBK, -1, (LPWSTR)wszUtf8, len);
       len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
       char *szUtf8=new char[len + 1]; 
       memset(szUtf8, 0, len + 1); 
       WideCharToMultiByte (CP_UTF8, 0, (LPCWSTR)wszUtf8, -1, (LPSTR)szUtf8, len, NULL,NULL);
       return szUtf8; 
}

void wfunction::UnZipStream(std::ifstream& inputFile,std::ofstream& outputFile)
{
	//this function convert \n to \r\n  why
	//ans fix \r with "open outputfile with binary mode" 
	io::filtering_streambuf<io::input> in;
	in.push(io::gzip_decompressor());
	in.push(inputFile);
	boost::iostreams::copy(in,outputFile);
}

void wfunction::ZipStream(std::ifstream& inputFile,std::ofstream& outputFile)
{
	io::filtering_streambuf<io::input> in;
	in.push(io::gzip_compressor());
	in.push(inputFile);
	boost::iostreams::copy(in,outputFile);
}
char * wfunction::ctp_time_char_convert(char * ori,int length)
{
	char * ret = new char[length];
	memset(ret,'\0',length);
	int j=0;
	for(int i=0;i>=0;i++)
	{
		if (ori[i]==':')
		{
			continue;
		}
		if (ori[i]=='\0')
		{
			break;
		}
		ret[j]=ori[i];
		j++;
		
	}
	return ret;
}
/*
#include<iostream>
#include<fstream>
int main()
{
	ifstream infile;
	string filename="d://data_trans.csv";
	wfunction wf;
	infile.open(filename.c_str());
	if(! infile.is_open()) //检测文件存在性
	{
		cerr << "Cannot openfile " << filename.c_str() << endl;
		getchar();
		return 1;
	}
	string tp;
	while(getline(infile,tp))
	{
		wf.splitstring(tp);
	}
	return 0;
}
*/