#include "Common.h"

#include "windows.h"
#include "commctrl.h"

//////////////////////////////////////////////////////////////////////

// ���׶�������
enum TRANACT
{
	TRANACT_BUY,
	TRANACT_SELL,
};

// �ֹɶ���
struct HoldStock
{
	std::string stockID; // ��ƱID
	int totalAmount; // ������
	int availableAmount; // ��������
	float refProfitLoss; // �ο�ӯ��
	float refPrimeCostPrice; // �ο��ɱ���
	float curPrice; // ��ǰ��
};

// ����ί�е�����
struct CommissionOrder
{
	std::string time; // ʱ��
	std::string stockID; // ��ƱID
	TRANACT tranAct; // ���׶���
	int commissionAmount; // ί������
	float commissionPrice; // ί�м۸�
	int dealAmount; // �ɽ�����
	float dealPrice; // �ɽ��۸�
};

// ���ճɽ�������
struct DealOrder
{
	std::string time; // ʱ��
	std::string stockID; // ��ƱID
	TRANACT tranAct; // ���׶���
	int dealAmount; // �ɽ�����
	float dealPrice; // �ɽ��۸�
};

// flush, max call frequency 30 sec
int FlushData();

/////////////////////////////////////////////////////////////////////////

// ͬ��˳��ҳ�ʼ��
int THSAPI_TongHuaShunInit();

// ��ȡ�˻����ý��
int THSAPI_GetAvailableMoney(float & availableMoney);

// ��ȡ�˻����ʲ�
int THSAPI_GetTotalAssets(float & totalAssets);

// ��ȡ�˻���Ʊ����ֵ
int THSAPI_GetAllStockMarketValue(float & allStockMarketValue);

// ��ȡ�ֹ��б�
int THSAPI_GetHoldStockList(std::list<HoldStock> & resultList);

// ��ȡ����ί���б�
int THSAPI_GetCommissionOrderList(std::list<CommissionOrder> & resultList);

// ��ȡ���ճɽ����б�
int THSAPI_GetDealOrderList(std::list<DealOrder> & resultList);

// ����ί���µ��ӿ�
int THSAPI_BuyStock(const char* stockId, const int buyAmount, const float price);

// ����ί���µ��ӿ�
int THSAPI_SellStock(const char* stockId, const int sellAmount, const float price);

