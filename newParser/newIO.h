// newIO.h: interface for the newIO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWIO_H__6AD9F5A8_6290_4864_8946_BC29304B6EC1__INCLUDED_)
#define AFX_NEWIO_H__6AD9F5A8_6290_4864_8946_BC29304B6EC1__INCLUDED_

#pragma warning(disable:4786)
#include "newPage.h"
#include <fstream.h>
#include <iostream.h>
#include <string>
#include <map>
//using namespace std;

const unsigned short MAXNAMESIZE=32;//���ݿ�������ϵ������������������Լ��������󳤶Ȳ�����32

class RelRecord //��ϵ��¼�࣬����Ķ��󽫴洢�����ݿ�Ŀ¼ҳ�С�
{
	friend class DBHeadPage;
private:
	unsigned long firstPageNo;//��ϵͷҳ��ҳ��,unsigned longռ4�ֽڣ�ȡֵ��Χ��0��4,294,967,295��
	//���ÿҳ4096�ֽڣ������ݿ���Դ洢16T�����ݡ�0Ϊ��Чҳ��
	char relName[MAXNAMESIZE];//��ϵ��
	explicit RelRecord();
	const unsigned long getFirstPageNo() const;//ȡ�ù�ϵͷҳ��ҳ�ţ���ֱ�ӷ���this->firstPageNo��
	const std::string getRelName() const;//ȡ�ù�ϵ�Ĺ�ϵ������this->relNameת��Ϊstring����Ȼ�󷵻ء�
	const Status setFirstPageNo(unsigned long firstPageNo);//�øù�ϵͷҳ��ҳ�ţ����жϲ�������ȷ�ԡ���������
	//firstPageNo<=0�򷵻�BADFIRSTPAGENO�����򷵻�OK��
	const Status setRelName(const std::string& relName);////�øù�ϵ�Ĺ�ϵ�������жϲ�������ȷ�ԡ���������
	//relNameΪ�ջ򳤶ȴ���MAXNAMESIZE�򷵻�BADRELNAME�����򷵻�OK��
	void initRelRec();//��ʼ���ù�ϵ��¼����this->firstPageNo��Ϊ0��
};
const unsigned long RELCNT = (PAGESIZE-4*sizeof(unsigned long)-MAXNAMESIZE)/sizeof(RelRecord);//���ݿ�Ŀ¼ҳ���ܹ��洢�Ĺ�ϵ��¼������
class DBHeadPage  //���ݿ�Ŀ¼ҳ�࣬�����洢���ݿ���Ϣ�Ϳ���ÿ����ϵ�Ĺ�ϵ��¼�������ж�����ݿ�Ŀ¼ҳ����
//nextDBHPNo���������ݿ�Ŀ¼ҳ����������nextFreePage�����п���ҳ��������
{
	friend class DB;
private:
	unsigned long relCnt;  //��ϵ��
	unsigned long nextFreePage;//��һ������ҳҳ�ţ�0Ϊ����һҳ
	unsigned long pageCnt;//ҳ������������ҳ��
	unsigned long nextDBHPNo;//��һ�����ݿ�ͷҳҳ�ţ�0Ϊ����һҳ
	char dbName[MAXNAMESIZE];//���ݿ���
	RelRecord relRecArray[RELCNT];//��ϵ��¼����
	char DBsignature[PAGESIZE-(RELCNT*sizeof(RelRecord)+MAXNAMESIZE+4*sizeof(unsigned long))]; //���ݿ�ǩ��,Ϊ�˲�ʹ�ڴ�Խ�磬
	//DBHeadPage��PageС16���ֽ�
	const Status setNextFreePage(unsigned long freePageNo);//����һ������ҳҳ�ţ����жϲ�������ȷ�ԡ�
	const Status setPageCnt(unsigned long pageCnt);//�ø����ݿ����ҳ�������жϲ�������ȷ�ԡ�
	const Status setRelCnt(unsigned long relCnt);//�ø����ݿ�Ĺ�ϵ�������жϲ�������ȷ�ԡ�
	const Status setNextDBHPNo(unsigned long nextDBHPNo);//����һ�����ݿ�Ŀ¼ҳҳ�ţ����жϲ�������ȷ�ԡ�
	const Status setDBName(const std::string &DBName);//�����ݿ����ƣ����жϲ�������ȷ�ԡ�
	const Status addRel(const std::string& tableName,unsigned long tableFirstPage);//���ϵ��¼�ļ������¼�һ����ϵ�����жϸ�
	//���ݿ�Ŀ¼ҳ�Ƿ��������ù�ϵ��¼�Ƿ��Ѿ����ڡ�
	const Status updataRel(const std::string& oldRelName, const std::string& newRelName);//����ĳ����ϵ��¼�����жϸù�ϵ
	//��¼�Ƿ��Ѿ����ڡ�
	const Status deleteRel(const std::string& tableName); //���ϵ��¼�ļ�����ɾ��һ����ϵ�����жϸù�ϵ��¼�Ƿ��Ѿ�
	//���ڡ�
public:
	explicit DBHeadPage();
	~DBHeadPage();
	const unsigned long getRelCnt() const;//���ع�ϵ��
	const unsigned long getNextFreePage() const;//������һ������ҳҳ��
	const unsigned long getPageCnt() const;//���ظ����ݿ����ҳ����
	const unsigned long getNextDBHPNo() const;//������һ�����ݿ�Ŀ¼ҳҳ��
	const std::string getDBName() const;//�������ݿ�����
	void init();//��ʼ�����ݿ�Ŀ¼ҳ��this->relCnt=0;this->nextFreePage=0;this->pageCnt=1;this->nextDBHPNo=0;
	//����this->relRecArray[]������ÿ����ϵ��¼��ʼ������
	const bool isFull() const;//�жϸ����ݿ�Ŀ¼ҳ�Ƿ�������
	const bool isEmpty() const;//�жϸ����ݿ�Ŀ¼ҳ�Ƿ��ѿա�
	const Status getRelFirstPage(const std::string &relName,unsigned long &firstPageNo) const;//ͨ����ϵ��ȥ���Ҹù�ϵ��ͷҳҳ�ţ�
	//���жϸù�ϵ��¼�Ƿ��Ѿ����ڡ�
};
class DB //���ݿ��࣬��װ�����ݿ�Ĳ�����
//�����½����ݿ⡢ɾ�����ݿ⡢�����ݿ⡢�ر����ݿ⡢�½���ϵ��ɾ����ϵ������ҳ���ͷ�ҳ����ҳ��дҳ��
{
	friend class DBManager;
private:
	std::string DBName; //���ݿ���
	mutable fstream file; //���ļ��Ĳ�������
	unsigned long openCnt;//���ݿ�Ĵ򿪴���
	DBHeadPage firstDBHP;//���ݿ��׸�Ŀ¼ҳ����openDB()�ж���
	explicit DB();//���캯����this->file.clear();this->openCnt=0;��
	explicit DB(const std::string &DBName);
	const Status intread(const unsigned long pageNo, Page* pagePtr) const;
	const Status intwrite(const unsigned long pageNo, const Page* pagePtr);
	const Status createDB(const std::string & DBName) ;  //�½�һ�����ݿ⣨�ļ��������жϲ�������ȷ�Ժ��½��ļ��ɹ�
	//���
	const Status destroyDB(const std::string & DBName) ; // ɾ��һ�����ݿ�,���жϲ�������ȷ�Ժ�ɾ���ļ��ɹ����
	const Status openDB(const std::string & DBName);  //�����ݿ⣬���жϲ�������ȷ�Ժʹ��ļ��ɹ����
	//���Ѿ�����openCnt++��
	const Status closeDB();//�ر����ݿ⣬���жϲ�������ȷ�Ժ͹ر��ļ��ɹ�������򿪴�������1��openCnt--��
	//�������ݿ�δ�����򷵻�FILENOTOPEN��
public:
	~DB();//��������������this->closeDB()���������ж�״̬�������򷵻ش�����Ϣ��
	const Status getFirstDBHP(const DBHeadPage* &dbHeadPage) const;
	const Status flushFirstDBHP();
	const Status createRel(const std::string& relName);//�����ݿ��д����ù�ϵ���ù�ϵͷҳ����ϵ������ϵҳ���顣
	//�뿼�Ǵ����ݿ�Ŀ¼ҳ�����������
	const Status destroyRel(const std::string& relName);//�����ݿ���ɾ���ù�ϵ�����Ҳ����ù�ϵ��¼�򷵻�RELNOTFOUND��
	//�뿼���ڶ�����ݿ�Ŀ¼ҳ���Ҹù�ϵ��¼�������
	const Status updataRel(const std::string& oldRelName, const std::string& newRelName);//����ĳ����ϵ��¼�����Ҳ�����
	//��ϵ��¼�򷵻�RELNOTFOUND���뿼���ڶ�����ݿ�Ŀ¼ҳ���Ҹù�ϵ��¼�������
	const Status allocatePage(unsigned long& pageNo);//Ϊ�����ݿ����һ����ҳ�����ڴ�������չPAGESIZE���ֽڣ����߿���ҳ��
	//��ȥ����û�п���ҳ����û�����ڴ�������չһ����ҳ��
	const Status disposePage(const unsigned long pageNo);//����ҳ�������ҳ���������жϲ�������ȷ�ԣ�Ȼ�󽫸�ҳ�������ҳ����
	const Status readPage(const unsigned long pageNo,Page* pagePtr) const;//�������и�ҳ�ŵ����ݶ���pagePtr�У����жϲ�����
	//��ȷ�ԡ�
	const Status writePage(const unsigned long pageNo,const Page* pagePtr);//���ڴ���pagePtr����д������и�ҳ�ŵ�λ�á�
	const unsigned long getOpenCnt() const;//�������ݿ�Ĵ򿪴�����
	const Status getRelFirstPageNo(const std::string &relName,unsigned long &firstPageNo) const;//ͨ����ϵ��ȥ���Ҹù�ϵ��ͷҳҳ�ţ�
	//���жϸù�ϵ��¼�Ƿ��Ѿ����ڡ�
	const std::string getDBName() const {return this->DBName;}
};
typedef std::map<std::string,DB*> DBMap;
class DBManager //���ݿ������,�ɹ���������ݿ⡣
{
private:
	DBMap dbMap;//���ݿ���󼯺ϣ�һ�����ݿ�����Ӧһ��DB��Ķ���
public:
	explicit DBManager();
	~DBManager();
	const Status createDataBase(const std::string & DBName);//�½�һ�����ݿ⣬���жϸ����ݿ��Ƿ��Ѿ�������
	//this->dbMap�С�
	const Status destroyDataBase(const std::string & DBName);//ɾ��һ�����ݿ⣬����this->dbMap�н��ü�¼ɾ����
	//���жϸ����ݿ��Ƿ������this->dbMap�С�
	const Status openDataBase(const std::string & DBName,DB* & database);//��һ�����ݿ⣬���жϸ����ݿ��Ƿ��Ѿ�������
	//this->dbMap�У����������������this->dbMap�У�����������¡����򿪵����ݿ���󷵻ص�database��
	const Status closeDataBase(const std::string & DBName);//�ر�һ�����ݿ⣬���жϸ����ݿ��Ƿ��Ѿ�������
	//this->dbMap�С��������ݿ��OpenCnt==0���this->dbMap��ɾ����
};
#endif // !defined(AFX_NEWIO_H__6AD9F5A8_6290_4864_8946_BC29304B6EC1__INCLUDED_)