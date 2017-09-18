#include "stdafx.h"
#include "WinHandle.h"
#include "TongHuaShun.h"
#include "Common.h"
#include "windows.h"
#include "commctrl.h"

static DSyncObj s_syncObjWinOP;

//////////////////////////////////////////////////////////////////////////
// find sub windows in tonghuashun

HWND s_hMainWin = NULL;
void setMainWin(HWND hWnd)
{
	DAutoSync sync(s_syncObjWinOP);

	s_hMainWin = hWnd;
}

int Hide_MainWin()
{
	DAutoSync sync(s_syncObjWinOP);

	HWND hMainWin = s_hMainWin;
	::ShowWindow(hMainWin, SW_MINIMIZE);
	return 0;
}


HWND findLeftTreeView(HWND hWnd) // and select expend 
{
	DAutoSync sync(s_syncObjWinOP);

	TESTLOG("findLeftTreeView#\n");
	HWND hLeftTreeView = NULL;
	HWND hChildL1 = NULL;
	for(;;) {
		hChildL1 = FindWindowExW(hWnd, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (0 == strcmp(szClassL1, "AfxMDIFrame42s"))
		{
			TESTLOG("findLeftTreeView# hWndL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);

			HWND hChildL2 = NULL;
			for(;;) {
				hChildL2 = FindWindowExW(hChildL1, hChildL2, 0, 0);
				if (hChildL2 == NULL)
					break;
				char szTitleL2[200];
				char szClassL2[200];
				char szWinTextL2[200];
				GetWindowText(hChildL2, szTitleL2, sizeof(szTitleL2) / sizeof(char)); 
				GetClassName(hChildL2, szClassL2, sizeof(szClassL2) / sizeof(char));
				GetWindowText(hChildL2, szWinTextL2, sizeof(szWinTextL2) / sizeof(char));
				if (0 == strcmp(szClassL2, "AfxWnd42s"))
				{
					TESTLOG("findLeftTreeView# hWndL2 = 0x%x szClassL2[%s] szWinTextL2[%s]\n",hChildL2, szClassL2,szWinTextL2);

					HWND hChildL3 = NULL;
					int iTimesHexinScrollWnd = 0;
					for(;;) {
						hChildL3 = FindWindowExW(hChildL2, hChildL3, 0, 0);
						if (hChildL3 == NULL)
							break;
						char szTitleL3[200];
						char szClassL3[200];
						char szWinTextL3[200];
						GetWindowText(hChildL3, szTitleL3, sizeof(szTitleL3) / sizeof(char)); 
						GetClassName(hChildL3, szClassL3, sizeof(szClassL3) / sizeof(char));
						GetWindowText(hChildL3, szWinTextL3, sizeof(szWinTextL3) / sizeof(char));
						if (0 == strcmp(szWinTextL3, "HexinScrollWnd"))
						{
							iTimesHexinScrollWnd++;
							//if (iTimesHexinScrollWnd == 2)  find all
							{
								TESTLOG("findLeftTreeView# hWndL3 = 0x%x szClassL3[%s] szWinTextL3[%s]\n",hChildL3, szClassL3,szWinTextL3);

								HWND hChildL4 = NULL;
								for(;;) {
									hChildL4 = FindWindowExW(hChildL3, hChildL4, 0, 0);
									if (hChildL4 == NULL)
										break;
									char szTitleL4[200];
									char szClassL4[200];
									char szWinTextL4[200];
									GetWindowText(hChildL4, szTitleL4, sizeof(szTitleL4) / sizeof(char)); 
									GetClassName(hChildL4, szClassL4, sizeof(szClassL4) / sizeof(char));
									GetWindowText(hChildL4, szWinTextL4, sizeof(szWinTextL4) / sizeof(char));

									if (0 == strcmp(szWinTextL4, "HexinScrollWnd2"))
									{
										TESTLOG("findLeftTreeView# hWndL4 = 0x%x szClassL4[%s] szWinTextL4[%s]\n",hChildL4, szClassL4,szWinTextL4);

										HWND hChildL5 = NULL;
										for(;;) {
											hChildL5 = FindWindowExW(hChildL4, hChildL5, 0, 0);
											if (hChildL5 == NULL)
												break;
											char szTitleL5[200];
											char szClassL5[200];
											char szWinTextL5[200];
											GetWindowText(hChildL5, szTitleL5, sizeof(szTitleL5) / sizeof(char)); 
											GetClassName(hChildL5, szClassL5, sizeof(szClassL5) / sizeof(char));
											GetWindowText(hChildL5, szWinTextL5, sizeof(szWinTextL5) / sizeof(char));

											TESTLOG("findLeftTreeView# hWndL5 = 0x%x szClassL5[%s] szWinTextL5[%s]\n",hChildL5, szClassL5,szWinTextL5);
											if (0 == strcmp(szClassL5, "SysTreeView32"))
											{
												if (0 == selectMasterTreeViewItem(hChildL5,-1))
												{
													return hChildL5;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return hLeftTreeView;
}

int selectMasterTreeViewItem(HWND hTreeView, int index = -1)
{
	DAutoSync sync(s_syncObjWinOP);

	TESTLOG("selectMasterTreeViewItem#\n");
	if (-1 == index)
	{
		TVITEM tvItem;
		ZeroMemory(&tvItem, sizeof(TVITEM));
		tvItem.cchTextMax = 512;
		tvItem.pszText = "X";
		tvItem.hItem = TreeView_GetRoot(hTreeView);
		// ����ѡ��
		TreeView_SelectItem(hTreeView, tvItem.hItem);
		Sleep(100);
		// ����ѡ��
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		TreeView_SelectItem(hTreeView, tvItem.hItem);
		Sleep(100);
		// ����
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		// �¹��깺
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		// ˫��
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		// �м�
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		// ��ѯ
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		for (int i = 0; i<10 ;i++)
		{
			if (TreeView_Expand(hTreeView, tvItem.hItem, TVE_EXPAND))
			{
				// �ʽ��Ʊ��ȡ
				tvItem.hItem = TreeView_GetChild(hTreeView, tvItem.hItem);
				if (!tvItem.hItem)
					continue;
				// չ���ɹ�
				// �ʽ��Ʊѡ��
				TreeView_SelectItem(hTreeView, tvItem.hItem);
				Sleep(100);

				//// ����ί��
				//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
				//TreeView_SelectItem(hTreeView, tvItem.hItem);
				//Sleep(100);

				//// ���ճɽ�
				//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
				//TreeView_SelectItem(hTreeView, tvItem.hItem);
				//Sleep(100);

				//// ��ʷί��
				//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
				//TreeView_SelectItem(hTreeView, tvItem.hItem);

				//// ��ʷ�ɽ�
				//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
				//TreeView_SelectItem(hTreeView, tvItem.hItem);

				//// �ʽ���ϸ
				//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
				//TreeView_SelectItem(hTreeView, tvItem.hItem);

				//// ���˵�
				//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
				//TreeView_SelectItem(hTreeView, tvItem.hItem);

				//// ���
				//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
				//TreeView_SelectItem(hTreeView, tvItem.hItem);

				//// �¹��깺��ѯ
				//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
				//TreeView_SelectItem(hTreeView, tvItem.hItem);

				if (NULL == tvItem.hItem)
				{
					return -1; // treeview����ȷ
				}

				//// ���������Ŀ
				//tvItem.hItem = TreeView_GetRoot(hTreeView);
				//// ����ѡ��
				//TreeView_SelectItem(hTreeView, tvItem.hItem);

				Sleep(200);
				return 0;
			}
		}
		return -1;
	}
	else if (0 == index) // ����ѡ��
	{
		TVITEM tvItem;
		ZeroMemory(&tvItem, sizeof(TVITEM));
		tvItem.cchTextMax = 512;
		tvItem.pszText = "X";
		tvItem.hItem = TreeView_GetRoot(hTreeView);
		// ����ѡ��
		TreeView_SelectItem(hTreeView, tvItem.hItem);
		Sleep(200);
		return 0;
	}
	else if (1 == index) // ����ѡ��
	{
		TVITEM tvItem;
		ZeroMemory(&tvItem, sizeof(TVITEM));
		tvItem.cchTextMax = 512;
		tvItem.pszText = "X";
		tvItem.hItem = TreeView_GetRoot(hTreeView);
		// ����ѡ��
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		TreeView_SelectItem(hTreeView, tvItem.hItem);
		Sleep(200);
		return 0;
	}
	else if (2 == index) // �ʽ��Ʊѡ��
	{
		TVITEM tvItem;
		ZeroMemory(&tvItem, sizeof(TVITEM));
		tvItem.cchTextMax = 512;
		tvItem.pszText = "X";
		tvItem.hItem = TreeView_GetRoot(hTreeView);
		// ����
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		// ����
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		// �¹��깺
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		// ˫��
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		// �м�
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		// ��ѯ
		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		for (int i = 0; i<10 ;i++)
		{
			if (TreeView_Expand(hTreeView, tvItem.hItem, TVE_EXPAND))
			{
				// �ʽ��Ʊ��ȡ
				tvItem.hItem = TreeView_GetChild(hTreeView, tvItem.hItem);
				if (!tvItem.hItem)
					continue;
				// չ���ɹ�
				// �ʽ��Ʊѡ��
				TreeView_SelectItem(hTreeView, tvItem.hItem);
				Sleep(200);
				return 0;
			}
		}
	}
	else if (3 == index) // ����ί��
	{
		//TVITEM tvItem;
		//ZeroMemory(&tvItem, sizeof(TVITEM));
		//tvItem.cchTextMax = 512;
		//tvItem.pszText = "X";
		//tvItem.hItem = TreeView_GetRoot(hTreeView);
		//// ����
		//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//// ����
		//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//// �¹��깺
		//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//// ˫��
		//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//// �м�
		//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//// ��ѯ
		//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//for (int i = 0; i<10 ;i++)
		//{
		//	if (TreeView_Expand(hTreeView, tvItem.hItem, TVE_EXPAND))
		//	{
		//		// �ʽ��Ʊ��ȡ
		//		tvItem.hItem = TreeView_GetChild(hTreeView, tvItem.hItem);
		//		if (!tvItem.hItem)
		//			continue;
		//		// չ���ɹ�

		//		// ����ί��
		//		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//		TreeView_SelectItem(hTreeView, tvItem.hItem);
		//		Sleep(200);

		//		return 0;
		//	}
		//}
	}
	else if (4 == index) // ���ճɽ�
	{
		//TVITEM tvItem;
		//ZeroMemory(&tvItem, sizeof(TVITEM));
		//tvItem.cchTextMax = 512;
		//tvItem.pszText = "X";
		//tvItem.hItem = TreeView_GetRoot(hTreeView);
		//// ����
		//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//// ����
		//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//// �¹��깺
		//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//// ˫��
		//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//// �м�
		//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//// ��ѯ
		//tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//for (int i = 0; i<10 ;i++)
		//{
		//	if (TreeView_Expand(hTreeView, tvItem.hItem, TVE_EXPAND))
		//	{
		//		// �ʽ��Ʊ��ȡ
		//		tvItem.hItem = TreeView_GetChild(hTreeView, tvItem.hItem);
		//		if (!tvItem.hItem)
		//			continue;
		//		// չ���ɹ�

		//		// ����ί��
		//		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);

		//		// ���ճɽ�
		//		tvItem.hItem = TreeView_GetNextSibling(hTreeView, tvItem.hItem);
		//		TreeView_SelectItem(hTreeView, tvItem.hItem);
		//		Sleep(200);

		//		return 0;
		//	}
		//}
	}
	return -1;
}				

HWND findZijinGupiaoWin(HWND hWnd)
{
	DAutoSync sync(s_syncObjWinOP);

	TESTLOG("findZijinGupiaoWin#\n");
	HWND hChildL1 = NULL;
	for(;;) {
		hChildL1 = FindWindowExW(hWnd, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));

		if (0 == strcmp(szClassL1, "AfxMDIFrame42s"))
		{
			TESTLOG("findZijinGupiaoWin# hWndL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);

			HWND hChildL2 = NULL;
			for(;;) {
				hChildL2 = FindWindowExW(hChildL1, hChildL2, 0, 0);
				if (hChildL2 == NULL)
					break;
				char szTitleL2[200];
				char szClassL2[200];
				char szWinTextL2[200];
				GetWindowText(hChildL2, szTitleL2, sizeof(szTitleL2) / sizeof(char)); 
				GetClassName(hChildL2, szClassL2, sizeof(szClassL2) / sizeof(char));
				GetWindowText(hChildL2, szWinTextL2, sizeof(szWinTextL2) / sizeof(char));
				TESTLOG("findZijinGupiaoWin# hWndL2 = 0x%x szClassL2[%s] szWinTextL2[%s]\n",hChildL2, szClassL2,szWinTextL2);

				HWND hChildL3 = NULL;
				int iTimesCheck = 0;
				int iFIndex = 0;
				for(;;) {
					hChildL3 = FindWindowExW(hChildL2, hChildL3, 0, 0);
					if (hChildL3 == NULL)
						break;
					char szTitleL3[200];
					char szClassL3[200];
					char szWinTextL3[200];
					GetWindowText(hChildL3, szTitleL3, sizeof(szTitleL3) / sizeof(char)); 
					GetClassName(hChildL3, szClassL3, sizeof(szClassL3) / sizeof(char));
					GetWindowText(hChildL3, szWinTextL3, sizeof(szWinTextL3) / sizeof(char));
					iFIndex++;
					if (0 == strcmp(szWinTextL3, "�ʽ����"))
					{
						iTimesCheck++;
					}
					if (0 == strcmp(szWinTextL3, "������"))
					{
						iTimesCheck++;
					}
					if (0 == strcmp(szWinTextL3, "���ý��"))
					{
						iTimesCheck++;
					}
					if (3 == iTimesCheck)
					{
						return hChildL2;
					}
				}
			}
		}
	}
	return NULL;
}

HWND findHoldStockWin(HWND hWnd)
{
	DAutoSync sync(s_syncObjWinOP);

	TESTLOG("findHoldStockWin#\n");
	
	HWND hZijinGupiao = findZijinGupiaoWin(hWnd);

	HWND hChildL1=NULL;
	for(;;) {
		hChildL1 = FindWindowExW(hZijinGupiao, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));

		if (0 == strcmp(szWinTextL1, "HexinScrollWnd"))
		{
			TESTLOG("findZijinGupiaoWin# hWndL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);

			HWND hChildL2 = NULL;
			for(;;) {
				hChildL2 = FindWindowExW(hChildL1, hChildL2, 0, 0);
				if (hChildL2 == NULL)
					break;
				char szTitleL2[200];
				char szClassL2[200];
				char szWinTextL2[200];
				GetWindowText(hChildL2, szTitleL2, sizeof(szTitleL2) / sizeof(char)); 
				GetClassName(hChildL2, szClassL2, sizeof(szClassL2) / sizeof(char));
				GetWindowText(hChildL2, szWinTextL2, sizeof(szWinTextL2) / sizeof(char));
				TESTLOG("findZijinGupiaoWin# hWndL2 = 0x%x szClassL2[%s] szWinTextL2[%s]\n",hChildL2, szClassL2,szWinTextL2);

				if (0 == strcmp(szWinTextL2, "HexinScrollWnd2"))
				{
					HWND hChildL3 = NULL;
					int iTimesCheck = 0;
					int iFIndex = 0;
					for(;;) {
						hChildL3 = FindWindowExW(hChildL2, hChildL3, 0, 0);
						if (hChildL3 == NULL)
							break;
						char szTitleL3[200];
						char szClassL3[200];
						char szWinTextL3[200];
						GetWindowText(hChildL3, szTitleL3, sizeof(szTitleL3) / sizeof(char)); 
						GetClassName(hChildL3, szClassL3, sizeof(szClassL3) / sizeof(char));
						GetWindowText(hChildL3, szWinTextL3, sizeof(szWinTextL3) / sizeof(char));
						iFIndex++;
						if (0 == strcmp(szClassL3, "CVirtualGridCtrl"))
						{
							return hChildL3;
						}
					}
				}
			}
		}
	}
	return NULL;
}

HWND findCommissionOrderWin(HWND hWnd)
{
	DAutoSync sync(s_syncObjWinOP);

	TESTLOG("findCommissionOrderWin#\n");

	HWND hChildL1 = NULL;
	for(;;) {
		hChildL1 = FindWindowExW(hWnd, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));

		if (0 == strcmp(szClassL1, "AfxMDIFrame42s"))
		{
			TESTLOG("findCommissionOrderWin# hWndL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);

			HWND hChildL2 = NULL;
			for(;;) {
				hChildL2 = FindWindowExW(hChildL1, hChildL2, 0, 0);
				if (hChildL2 == NULL)
					break;
				char szTitleL2[200];
				char szClassL2[200];
				char szWinTextL2[200];
				GetWindowText(hChildL2, szTitleL2, sizeof(szTitleL2) / sizeof(char)); 
				GetClassName(hChildL2, szClassL2, sizeof(szClassL2) / sizeof(char));
				GetWindowText(hChildL2, szWinTextL2, sizeof(szWinTextL2) / sizeof(char));
				TESTLOG("findCommissionOrderWin# hWndL2 = 0x%x szClassL2[%s] szWinTextL2[%s]\n",hChildL2, szClassL2,szWinTextL2);

				HWND hChild_HexinScrollWnd = NULL;
				HWND hChildL3 = NULL;
				int iTimesCheck = 0;
				int iFIndex = 0;
				for(;;) {
					hChildL3 = FindWindowExW(hChildL2, hChildL3, 0, 0);
					if (hChildL3 == NULL)
						break;
					char szTitleL3[200];
					char szClassL3[200];
					char szWinTextL3[200];
					GetWindowText(hChildL3, szTitleL3, sizeof(szTitleL3) / sizeof(char)); 
					GetClassName(hChildL3, szClassL3, sizeof(szClassL3) / sizeof(char));
					GetWindowText(hChildL3, szWinTextL3, sizeof(szWinTextL3) / sizeof(char));
					iFIndex++;

					//TESTLOG("findCommissionOrderWin# hWndL3 = 0x%x szClassL3[%s] szWinTextL3[%s]\n",hChildL3, szClassL3,szWinTextL3);
					
					if (0 == strcmp(szWinTextL3, "��ʾ�ֱʳɽ�"))
					{
						iTimesCheck++;
					}
					if (0 == strcmp(szWinTextL3, "��ͬ���"))
					{
						iTimesCheck++;
					}
					if (0 == strcmp(szWinTextL3, "��ʾ������¼"))
					{
						iTimesCheck++;
					}
					if (0 == strcmp(szWinTextL3, "HexinScrollWnd"))
					{
						hChild_HexinScrollWnd = hChildL3;
					}
					if (3 == iTimesCheck && NULL != hChild_HexinScrollWnd)
					{
						// �ҵ��� hChild_HexinScrollWnd
						HWND hChildL4 = NULL;
						for(;;) {
							hChildL4 = FindWindowExW(hChildL3, hChildL4, 0, 0);
							if (hChildL4 == NULL)
								break;
							char szTitleL4[200];
							char szClassL4[200];
							char szWinTextL4[200];
							GetWindowText(hChildL4, szTitleL4, sizeof(szTitleL4) / sizeof(char)); 
							GetClassName(hChildL4, szClassL4, sizeof(szClassL4) / sizeof(char));
							GetWindowText(hChildL4, szWinTextL4, sizeof(szWinTextL4) / sizeof(char));
							//TESTLOG("findCommissionOrderWin# hWndL4 = 0x%x szClassL4[%s] szWinTextL4[%s]\n",hChildL4, szClassL4,szWinTextL4);
							if (0 == strcmp(szWinTextL4, "HexinScrollWnd2"))
							{
								// �ҵ��� HexinScrollWnd2
								HWND hChildL5 = NULL;
								for(;;) {
									hChildL5 = FindWindowExW(hChildL4, hChildL5, 0, 0);
									if (hChildL5 == NULL)
										break;
									char szTitleL5[200];
									char szClassL5[200];
									char szWinTextL5[200];
									GetWindowText(hChildL5, szTitleL5, sizeof(szTitleL5) / sizeof(char)); 
									GetClassName(hChildL5, szClassL5, sizeof(szClassL5) / sizeof(char));
									GetWindowText(hChildL5, szWinTextL5, sizeof(szWinTextL5) / sizeof(char));
									//TESTLOG("findCommissionOrderWin# hWndL5 = 0x%x szClassL5[%s] szWinTextL5[%s]\n",hChildL5, szClassL5,szWinTextL5);
									if (0 == strcmp(szClassL5, "CVirtualGridCtrl"))
									{
										// �ҵ��˲ο�CVirtualGridCtrl������CtrlV��������
										std::string buf;
										// try copy 3 times
										for(int i=0;i<5;i++)
										{
											Sleep(200);
											bool bCtrlV = getCtrlVFormWin(hChildL5,buf);
											if(buf.length()>30)
											{
												int pos=buf.find("ί��ʱ��");
												if (bCtrlV && pos >= 0 && pos<20)
												{
													return hChildL5;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return NULL;
}

HWND findDealOrderWin(HWND hWnd)
{
	DAutoSync sync(s_syncObjWinOP);

	TESTLOG("findDealOrderWin#\n");
	HWND hChildL1 = NULL;
	for(;;) {
		hChildL1 = FindWindowExW(hWnd, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));

		if (0 == strcmp(szClassL1, "AfxMDIFrame42s"))
		{
			TESTLOG("findCommissionOrderWin# hWndL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);

			HWND hChildL2 = NULL;
			for(;;) {
				hChildL2 = FindWindowExW(hChildL1, hChildL2, 0, 0);
				if (hChildL2 == NULL)
					break;
				char szTitleL2[200];
				char szClassL2[200];
				char szWinTextL2[200];
				GetWindowText(hChildL2, szTitleL2, sizeof(szTitleL2) / sizeof(char)); 
				GetClassName(hChildL2, szClassL2, sizeof(szClassL2) / sizeof(char));
				GetWindowText(hChildL2, szWinTextL2, sizeof(szWinTextL2) / sizeof(char));
				TESTLOG("findCommissionOrderWin# hWndL2 = 0x%x szClassL2[%s] szWinTextL2[%s]\n",hChildL2, szClassL2,szWinTextL2);

				HWND hChild_HexinScrollWnd = NULL;
				HWND hChildL3 = NULL;
				int iTimesCheck = 0;
				int iFIndex = 0;
				for(;;) {
					hChildL3 = FindWindowExW(hChildL2, hChildL3, 0, 0);
					if (hChildL3 == NULL)
						break;
					char szTitleL3[200];
					char szClassL3[200];
					char szWinTextL3[200];
					GetWindowText(hChildL3, szTitleL3, sizeof(szTitleL3) / sizeof(char)); 
					GetClassName(hChildL3, szClassL3, sizeof(szClassL3) / sizeof(char));
					GetWindowText(hChildL3, szWinTextL3, sizeof(szWinTextL3) / sizeof(char));
					iFIndex++;

					//TESTLOG("findCommissionOrderWin# hWndL3 = 0x%x szClassL3[%s] szWinTextL3[%s]\n",hChildL3, szClassL3,szWinTextL3);

					if (0 == strcmp(szWinTextL3, "��ʾ�ֱʳɽ�"))
					{
						iTimesCheck++;
					}
					if (0 == strcmp(szWinTextL3, "��ͬ���"))
					{
						iTimesCheck++;
					}
					if (0 == strcmp(szWinTextL3, "��ʾ������¼"))
					{
						iTimesCheck++;
					}
					if (0 == strcmp(szWinTextL3, "HexinScrollWnd"))
					{
						hChild_HexinScrollWnd = hChildL3;
					}
					if (3 == iTimesCheck && NULL != hChild_HexinScrollWnd)
					{
						// �ҵ��� hChild_HexinScrollWnd
						HWND hChildL4 = NULL;
						for(;;) {
							hChildL4 = FindWindowExW(hChildL3, hChildL4, 0, 0);
							if (hChildL4 == NULL)
								break;
							char szTitleL4[200];
							char szClassL4[200];
							char szWinTextL4[200];
							GetWindowText(hChildL4, szTitleL4, sizeof(szTitleL4) / sizeof(char)); 
							GetClassName(hChildL4, szClassL4, sizeof(szClassL4) / sizeof(char));
							GetWindowText(hChildL4, szWinTextL4, sizeof(szWinTextL4) / sizeof(char));
							//TESTLOG("findCommissionOrderWin# hWndL4 = 0x%x szClassL4[%s] szWinTextL4[%s]\n",hChildL4, szClassL4,szWinTextL4);
							if (0 == strcmp(szWinTextL4, "HexinScrollWnd2"))
							{
								// �ҵ��� HexinScrollWnd2
								HWND hChildL5 = NULL;
								for(;;) {
									hChildL5 = FindWindowExW(hChildL4, hChildL5, 0, 0);
									if (hChildL5 == NULL)
										break;
									char szTitleL5[200];
									char szClassL5[200];
									char szWinTextL5[200];
									GetWindowText(hChildL5, szTitleL5, sizeof(szTitleL5) / sizeof(char)); 
									GetClassName(hChildL5, szClassL5, sizeof(szClassL5) / sizeof(char));
									GetWindowText(hChildL5, szWinTextL5, sizeof(szWinTextL5) / sizeof(char));
									//TESTLOG("findCommissionOrderWin# hWndL5 = 0x%x szClassL5[%s] szWinTextL5[%s]\n",hChildL5, szClassL5,szWinTextL5);
									if (0 == strcmp(szClassL5, "CVirtualGridCtrl"))
									{
										// �ҵ��˲ο�CVirtualGridCtrl������CtrlV��������
										std::string buf;
										// try copy 5 times
										for(int i=0;i<5;i++)
										{
											Sleep(200);
											bool bCtrlV = getCtrlVFormWin(hChildL5,buf);
											if(buf.length()>30)
											{
												int pos=buf.find("�ɽ�ʱ��");
												if (bCtrlV && pos >= 0 && pos<20)
												{
													return hChildL5;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return NULL;
}

HWND findBuyWin(HWND hWnd)
{
	DAutoSync sync(s_syncObjWinOP);

	TESTLOG("findBuyWin#\n");

	HWND hChildL1 = NULL;
	for(;;) {
		hChildL1 = FindWindowExW(hWnd, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));

		if (0 == strcmp(szClassL1, "AfxMDIFrame42s"))
		{
			TESTLOG("findBuyWin# hWndL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);

			HWND hChildL2 = NULL;
			for(;;) {
				hChildL2 = FindWindowExW(hChildL1, hChildL2, 0, 0);
				if (hChildL2 == NULL)
					break;
				char szTitleL2[200];
				char szClassL2[200];
				char szWinTextL2[200];
				GetWindowText(hChildL2, szTitleL2, sizeof(szTitleL2) / sizeof(char)); 
				GetClassName(hChildL2, szClassL2, sizeof(szClassL2) / sizeof(char));
				GetWindowText(hChildL2, szWinTextL2, sizeof(szWinTextL2) / sizeof(char));
				TESTLOG("findBuyWin# hWndL2 = 0x%x szClassL2[%s] szWinTextL2[%s]\n",hChildL2, szClassL2,szWinTextL2);

				HWND hChildL3 = NULL;
				int iFIndex = 0;
				for(;;) {
					hChildL3 = FindWindowExW(hChildL2, hChildL3, 0, 0);
					if (hChildL3 == NULL)
						break;
					char szTitleL3[200];
					char szClassL3[200];
					char szWinTextL3[200];
					GetWindowText(hChildL3, szTitleL3, sizeof(szTitleL3) / sizeof(char)); 
					GetClassName(hChildL3, szClassL3, sizeof(szClassL3) / sizeof(char));
					GetWindowText(hChildL3, szWinTextL3, sizeof(szWinTextL3) / sizeof(char));
					iFIndex++;
					if (20 == iFIndex && 0 == strcmp(szWinTextL3, "�����Ʊ"))
					{
						TESTLOG("findBuyWin# hWndL3 = 0x%x szClassL3[%s] szWinTextL3[%s]\n",hChildL3, szClassL3,szWinTextL3);
						return hChildL2;
					}
				}
			}
		}
	}
	return NULL;
}

HWND findSellWin(HWND hWnd)
{
	DAutoSync sync(s_syncObjWinOP);

	TESTLOG("findSellWin#\n");

	HWND hChildL1 = NULL;
	for(;;) {
		hChildL1 = FindWindowExW(hWnd, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));

		if (0 == strcmp(szClassL1, "AfxMDIFrame42s"))
		{
			TESTLOG("findSellWin# hWndL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hChildL1, szClassL1,szWinTextL1);

			HWND hChildL2 = NULL;
			for(;;) {
				hChildL2 = FindWindowExW(hChildL1, hChildL2, 0, 0);
				if (hChildL2 == NULL)
					break;
				char szTitleL2[200];
				char szClassL2[200];
				char szWinTextL2[200];
				GetWindowText(hChildL2, szTitleL2, sizeof(szTitleL2) / sizeof(char)); 
				GetClassName(hChildL2, szClassL2, sizeof(szClassL2) / sizeof(char));
				GetWindowText(hChildL2, szWinTextL2, sizeof(szWinTextL2) / sizeof(char));
				TESTLOG("findSellWin# hWndL2 = 0x%x szClassL2[%s] szWinTextL2[%s]\n",hChildL2, szClassL2,szWinTextL2);

				HWND hChildL3 = NULL;
				int iFIndex = 0;
				for(;;) {
					hChildL3 = FindWindowExW(hChildL2, hChildL3, 0, 0);
					if (hChildL3 == NULL)
						break;
					char szTitleL3[200];
					char szClassL3[200];
					char szWinTextL3[200];
					GetWindowText(hChildL3, szTitleL3, sizeof(szTitleL3) / sizeof(char)); 
					GetClassName(hChildL3, szClassL3, sizeof(szClassL3) / sizeof(char));
					GetWindowText(hChildL3, szWinTextL3, sizeof(szWinTextL3) / sizeof(char));
					iFIndex++;
					if (18 == iFIndex && 0 == strcmp(szWinTextL3, "������Ʊ"))
					{
						TESTLOG("findSellWin# hWndL3 = 0x%x szClassL3[%s] szWinTextL3[%s]\n",hChildL3, szClassL3,szWinTextL3);
						return hChildL2;
					}
				}
			}
		}
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
// find main win in desktop

HWND FindTongHuaShunMainWin()
{
	DAutoSync sync(s_syncObjWinOP);

	return FindWindowW(0, L"���Ϲ�Ʊ����ϵͳ5.0");
}

int CancelAllMainWin()
{
	DAutoSync sync(s_syncObjWinOP);

	int iCloseZhangDieXianZhi =  CloseZhangDieXianZhi_Cancel();
	int iCloseWeiTuoQueRen = CloseWeiTuoQueRen_Cancel();
	int iCloseTijiaoShiBai = CloseTijiaoShiBai();
	int iCloseTijiaoChengGong = CloseTijiaoChengGong();
	if (0 == iCloseZhangDieXianZhi &&
		0 == iCloseWeiTuoQueRen &&
		0 == iCloseTijiaoShiBai &&
		0 ==iCloseTijiaoChengGong
		)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

// zhangdiexianzhi
HWND Find_ZhangDieXianZhi()
{
	DAutoSync sync(s_syncObjWinOP);

	HWND hZhangDieXianZhiTishi = NULL;
	HWND hWndDesktop = GetDesktopWindow();
	HWND hMainWin = NULL;
	for(;;) {
		hMainWin = FindWindowExW(hWndDesktop, hMainWin, 0, 0);
		if (hMainWin == NULL)
			break;
		char szTitleMain[200];
		char szClasseMain[200];
		char szWinTexteMain[200];
		GetWindowText(hMainWin, szTitleMain, sizeof(szTitleMain) / sizeof(char));
		GetClassName(hMainWin, szClasseMain, sizeof(szClasseMain) / sizeof(char));
		GetWindowText(hMainWin, szWinTexteMain, sizeof(szWinTexteMain) / sizeof(char));
		HWND hChildL1 = NULL;
		int index = 0;
		int iCheckCount = 0;
		for(;;) {
			hChildL1 = FindWindowExW(hMainWin, hChildL1, 0, 0);
			if (hChildL1 == NULL)
				break;
			index++;
			char szTitleL1[200];
			char szClassL1[200];
			char szWinTextL1[200];
			GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
			GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
			GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
			//printf("Find_ZhangDieXianZhi# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
			if (1 == index && 0 == strcmp("Static", szClassL1))
			{
				iCheckCount++;
			}
			if (4 == index && 0 == strcmp("Static", szClassL1) && 0 == strcmp("��ʾ��Ϣ", szWinTextL1))
			{
				iCheckCount++;
			}
			if (iCheckCount == 2)
			{
				//printf("Find_ZhangDieXianZhi# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
				hZhangDieXianZhiTishi = hMainWin;
				return hZhangDieXianZhiTishi;
			}
		}
	}
	return hZhangDieXianZhiTishi;
}
HWND FindZhangDieXianZhiCloseBtn(HWND hZhangDieXianZhi)
{
	DAutoSync sync(s_syncObjWinOP);

	HWND hCloseBtn = NULL;
	HWND hChildL1 = NULL;
	int index = 0;
	int iCheckCount = 0;
	for(;;) {
		hChildL1 = FindWindowExW(hZhangDieXianZhi, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		index++;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (3 == index)
		{
			hCloseBtn = hChildL1;
			break;
		}
	}
	return hCloseBtn;
}

int CloseZhangDieXianZhi_Cancel()
{
	DAutoSync sync(s_syncObjWinOP);

	for (int i=0; i<500; i++)
	{
		HWND hZhangDieXianZhi = Find_ZhangDieXianZhi();
		if (NULL != hZhangDieXianZhi)
		{
			HWND hCloseBtn = FindZhangDieXianZhiCloseBtn(hZhangDieXianZhi);
			if (NULL != hCloseBtn)
			{
				PostMessage(hCloseBtn,WM_LBUTTONDOWN,0,0);
				Sleep(10);
				PostMessage(hCloseBtn,WM_LBUTTONUP,0,0);
			}
			Sleep(10);
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

// WeiTuoQueRen
HWND Find_WeiTuoQueRen(int& iflag,string& id, int& amount, float& price)
{
	DAutoSync sync(s_syncObjWinOP);

	HWND hWeiTuoQueRen = NULL;
	HWND hWndDesktop = GetDesktopWindow();
	HWND hMainWin = NULL;
	for(;;) {
		hMainWin = FindWindowExW(hWndDesktop, hMainWin, 0, 0);
		if (hMainWin == NULL)
			break;
		char szTitleMain[200];
		char szClasseMain[200];
		char szWinTexteMain[200];
		GetWindowText(hMainWin, szTitleMain, sizeof(szTitleMain) / sizeof(char));
		GetClassName(hMainWin, szClasseMain, sizeof(szClasseMain) / sizeof(char));
		GetWindowText(hMainWin, szWinTexteMain, sizeof(szWinTexteMain) / sizeof(char));
		HWND hChildL1 = NULL;
		int index = 0;
		int iCheckCount = 0;
		for(;;) {
			hChildL1 = FindWindowExW(hMainWin, hChildL1, 0, 0);
			if (hChildL1 == NULL)
				break;
			index++;
			char szTitleL1[200];
			char szClassL1[200];
			char szWinTextL1[200];
			GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
			GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
			GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
			if (0 == strcmp(szWinTextL1,""))
			{
				SendMessage(hChildL1, WM_GETTEXT, 200, long(szWinTextL1));
			}
			char szWinText10Caption[200];
			//printf("Find_WeiTuoQueRen# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
			if (10 == index && 0 == strcmp("Static", szClassL1))
			{
				strcpy_s(szWinText10Caption, 200, szWinTextL1);
				iCheckCount++;
			}
			if (12 == index && 0 == strcmp("Static", szClassL1) && 0 == strcmp("ί��ȷ��", szWinTextL1))
			{
				iCheckCount++;
			}
			if (iCheckCount == 2)
			{
				char szId[200];
				char szAmount[200];
				char szPrice[200];
				DWORD isize = 200;
				if (DStr::InstrA(szWinText10Caption,"����۸�")>0)
				{
					iflag = 0;
					DStr::GetSubStr_BetweenSpecialStrA(szWinText10Caption,"֤ȯ���룺","����۸�",szId,isize);
					DStr::TrimA(szId);
					DStr::GetSubStr_BetweenSpecialStrA(szWinText10Caption,"����������","Ԥ�����",szAmount,isize);
					DStr::TrimA(szAmount);
					DStr::GetSubStr_BetweenSpecialStrA(szWinText10Caption,"����۸�","��������",szPrice,isize);
					DStr::TrimA(szPrice);
				}
				if (DStr::InstrA(szWinText10Caption,"�����۸�")>0)
				{
					// �ɶ��ʺţ�A375867637֤ȯ���룺601988�����۸�4.020����������100Ԥ����396.000���Ƿ�ȷ����������ί�У�
					iflag = 1;
					DStr::GetSubStr_BetweenSpecialStrA(szWinText10Caption,"֤ȯ���룺","�����۸�",szId,isize);
					DStr::TrimA(szId);
					DStr::GetSubStr_BetweenSpecialStrA(szWinText10Caption,"����������","Ԥ�����",szAmount,isize);
					DStr::TrimA(szAmount);
					DStr::GetSubStr_BetweenSpecialStrA(szWinText10Caption,"�����۸�","��������",szPrice,isize);
					DStr::TrimA(szPrice);
				}
				id = string(szId);
				int iamount = 0;
				sscanf_s(szAmount ,"%d", &iamount);	
				amount = iamount;
				float fprice = 0.0f;
				sscanf_s(szPrice ,"%f", &fprice);
				price = fprice;

				//printf("Find_WeiTuoQueRen# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
				hWeiTuoQueRen = hMainWin;
				return hWeiTuoQueRen;
			}
		}
	}
	return hWeiTuoQueRen;
}
HWND FindWeiTuoQueRenOKBtn(HWND hWeiTuoQueRen)
{
	DAutoSync sync(s_syncObjWinOP);

	HWND hOKBtn = NULL;
	HWND hChildL1 = NULL;
	int index = 0;
	int iCheckCount = 0;
	for(;;) {
		hChildL1 = FindWindowExW(hWeiTuoQueRen, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		index++;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (1 == index)
		{
			hOKBtn = hChildL1;
			break;
		}
	}
	return hOKBtn;
}
HWND FindWeiTuoQueRenCancelBtn(HWND hWeiTuoQueRen)
{
	DAutoSync sync(s_syncObjWinOP);

	HWND hCancelBtn = NULL;
	HWND hChildL1 = NULL;
	int index = 0;
	int iCheckCount = 0;
	for(;;) {
		hChildL1 = FindWindowExW(hWeiTuoQueRen, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		index++;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (2 == index)
		{
			hCancelBtn = hChildL1;
			break;
		}
	}
	return hCancelBtn;
}
int CloseWeiTuoQueRen_OK()
{
	DAutoSync sync(s_syncObjWinOP);

	for (int i=0; i<500; i++)
	{
		int iFlag =0;
		string sId;
		int iAmount = 0;
		float fPrice = 0.0f;
		HWND hWeiTuoQueRen = Find_WeiTuoQueRen(iFlag,sId, iAmount,fPrice);
		if (NULL != hWeiTuoQueRen)
		{
			HWND hOKBtn = FindWeiTuoQueRenOKBtn(hWeiTuoQueRen);
			if (NULL != hOKBtn)
			{
				PostMessage(hOKBtn,WM_LBUTTONDOWN,0,0);
				Sleep(10);
				PostMessage(hOKBtn,WM_LBUTTONUP,0,0);
			}
			Sleep(10);
		}
		else
		{
			return 0;
		}
	}
	return -1;
}
int CloseWeiTuoQueRen_Cancel()
{
	DAutoSync sync(s_syncObjWinOP);

	for (int i=0; i<500; i++)
	{
		int iFlag =0;
		string sId;
		int iAmount = 0;
		float fPrice = 0.0f;
		HWND hWeiTuoQueRen = Find_WeiTuoQueRen(iFlag,sId, iAmount,fPrice);
		if (NULL != hWeiTuoQueRen)
		{
			HWND hCancelBtn = FindWeiTuoQueRenCancelBtn(hWeiTuoQueRen);
			if (NULL != hCancelBtn)
			{
				PostMessage(hCancelBtn,WM_LBUTTONDOWN,0,0);
				Sleep(10);
				PostMessage(hCancelBtn,WM_LBUTTONUP,0,0);
			}
			Sleep(10);
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

// TiJiaoShiBai
HWND Find_TijiaoShiBai()
{
	DAutoSync sync(s_syncObjWinOP);

	HWND hTijiaoShiBai = NULL;
	HWND hWndDesktop = GetDesktopWindow();
	HWND hMainWin = NULL;
	for(;;) {
		hMainWin = FindWindowExW(hWndDesktop, hMainWin, 0, 0);
		if (hMainWin == NULL)
			break;
		char szTitleMain[200];
		char szClasseMain[200];
		char szWinTexteMain[200];
		GetWindowText(hMainWin, szTitleMain, sizeof(szTitleMain) / sizeof(char));
		GetClassName(hMainWin, szClasseMain, sizeof(szClasseMain) / sizeof(char));
		GetWindowText(hMainWin, szWinTexteMain, sizeof(szWinTexteMain) / sizeof(char));
		HWND hChildL1 = NULL;
		int index = 0;
		int iCheckCount = 0;
		for(;;) {
			hChildL1 = FindWindowExW(hMainWin, hChildL1, 0, 0);
			if (hChildL1 == NULL)
				break;
			index++;
			char szTitleL1[200];
			char szClassL1[200];
			char szWinTextL1[200];
			GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
			GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
			GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
			if (0 == strcmp(szWinTextL1,""))
			{
				SendMessage(hChildL1, WM_GETTEXT, 200, long(szWinTextL1));
			}
			//printf("Find_ZhangDieXianZhi# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
			if (2 == index && 0 == strcmp("Button", szClassL1) && 0 == strcmp("��ѯ��ǰί��", szWinTextL1))
			{
				iCheckCount++;
			}
			if (3 == index && 0 == strcmp("Static", szClassL1) && DStr::InstrA(szWinTextL1,"�ɹ��ύ")<0)
			{
				iCheckCount++;
			}
			if (4 == index && 0 == strcmp("Static", szClassL1) && 0 == strcmp("��ʾ", szWinTextL1))
			{
				iCheckCount++;
			}
			if (iCheckCount == 3)
			{
				//printf("Find_ZhangDieXianZhi# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
				hTijiaoShiBai = hMainWin;
				return hTijiaoShiBai;
			}
		}
	}
	return hTijiaoShiBai;
}
HWND FindTijiaoShiBaiOKBtn(HWND hTijiaoShiBai)
{
	DAutoSync sync(s_syncObjWinOP);

	HWND hOKBtn = NULL;
	HWND hChildL1 = NULL;
	int index = 0;
	int iCheckCount = 0;
	for(;;) {
		hChildL1 = FindWindowExW(hTijiaoShiBai, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		index++;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (1 == index)
		{
			hOKBtn = hChildL1;
			break;
		}
	}
	return hOKBtn;
}
int CloseTijiaoShiBai()
{
	DAutoSync sync(s_syncObjWinOP);

	for (int i=0; i<500; i++)
	{
		HWND hTijiaoShiBai = Find_TijiaoShiBai();
		if (NULL != hTijiaoShiBai)
		{
			HWND hOKBtn = FindTijiaoShiBaiOKBtn(hTijiaoShiBai);
			if (NULL != hOKBtn)
			{
				PostMessage(hOKBtn,WM_LBUTTONDOWN,0,0);
				Sleep(10);
				PostMessage(hOKBtn,WM_LBUTTONUP,0,0);
			}
			Sleep(10);
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

// TijiaoChengGong
HWND Find_TijiaoChengGong()
{
	DAutoSync sync(s_syncObjWinOP);

	HWND hTijiaoChengGong = NULL;
	HWND hWndDesktop = GetDesktopWindow();
	HWND hMainWin = NULL;
	for(;;) {
		hMainWin = FindWindowExW(hWndDesktop, hMainWin, 0, 0);
		if (hMainWin == NULL)
			break;
		char szTitleMain[200];
		char szClasseMain[200];
		char szWinTexteMain[200];
		GetWindowText(hMainWin, szTitleMain, sizeof(szTitleMain) / sizeof(char));
		GetClassName(hMainWin, szClasseMain, sizeof(szClasseMain) / sizeof(char));
		GetWindowText(hMainWin, szWinTexteMain, sizeof(szWinTexteMain) / sizeof(char));
		HWND hChildL1 = NULL;
		int index = 0;
		int iCheckCount = 0;
		for(;;) {
			hChildL1 = FindWindowExW(hMainWin, hChildL1, 0, 0);
			if (hChildL1 == NULL)
				break;
			index++;
			char szTitleL1[200];
			char szClassL1[200];
			char szWinTextL1[200];
			GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
			GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
			GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
			if (0 == strcmp(szWinTextL1,""))
			{
				SendMessage(hChildL1, WM_GETTEXT, 200, long(szWinTextL1));
			}
			//printf("Find_ZhangDieXianZhi# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
			if (2 == index && 0 == strcmp("Button", szClassL1) && 0 == strcmp("��ѯ��ǰί��", szWinTextL1))
			{
				iCheckCount++;
			}
			if (3 == index && 0 == strcmp("Static", szClassL1) && DStr::InstrA(szWinTextL1,"�ɹ��ύ")>=0)
			{
				iCheckCount++;
			}
			if (4 == index && 0 == strcmp("Static", szClassL1) && 0 == strcmp("��ʾ", szWinTextL1))
			{
				iCheckCount++;
			}
			if (iCheckCount == 3)
			{
				//printf("Find_ZhangDieXianZhi# hChildL1 = 0x%x szClassL1[%s] szWinTextL1[%s]\n",hMainWin, szClassL1,szWinTextL1);
				hTijiaoChengGong = hMainWin;
				return hTijiaoChengGong;
			}
		}
	}
	return hTijiaoChengGong;
}
HWND FindTijiaoChengGongOKBtn(HWND hTijiaoChengGong)
{
	DAutoSync sync(s_syncObjWinOP);

	HWND hOKBtn = NULL;
	HWND hChildL1 = NULL;
	int index = 0;
	int iCheckCount = 0;
	for(;;) {
		hChildL1 = FindWindowExW(hTijiaoChengGong, hChildL1, 0, 0);
		if (hChildL1 == NULL)
			break;
		index++;
		char szTitleL1[200];
		char szClassL1[200];
		char szWinTextL1[200];
		GetWindowText(hChildL1, szTitleL1, sizeof(szTitleL1) / sizeof(char));
		GetClassName(hChildL1, szClassL1, sizeof(szClassL1) / sizeof(char));
		GetWindowText(hChildL1, szWinTextL1, sizeof(szWinTextL1) / sizeof(char));
		if (1 == index)
		{
			hOKBtn = hChildL1;
			break;
		}
	}
	return hOKBtn;
}
int CloseTijiaoChengGong(){

	DAutoSync sync(s_syncObjWinOP);

	for (int i=0; i<500; i++)
	{
		HWND hTijiaoChengGong = Find_TijiaoChengGong();
		if (NULL != hTijiaoChengGong)
		{
			HWND hOKBtn = FindTijiaoChengGongOKBtn(hTijiaoChengGong);
			if (NULL != hOKBtn)
			{
				PostMessage(hOKBtn,WM_LBUTTONDOWN,0,0);
				Sleep(10);
				PostMessage(hOKBtn,WM_LBUTTONUP,0,0);
			}
			Sleep(10);
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

int Flush_F5(int wait_msec)
{
	DAutoSync sync(s_syncObjWinOP);

	HWND hWndWin = FindTongHuaShunMainWin();
	::PostMessage(hWndWin, WM_KEYDOWN, VK_F5, 0);
	Sleep(5);
	::PostMessage(hWndWin, WM_KEYUP, VK_F5, 0);
	Sleep(wait_msec);
	return 0;
}

bool isAvailableClipboard()
{
	DAutoSync sync(s_syncObjWinOP);

	bool bRet = false;
	if (::OpenClipboard(NULL))
	{
		
		if (::CloseClipboard())
		{
			bRet = true;
		}
	}
	return bRet;
}

bool setClipboard(std::string in_buf)
{
	DAutoSync sync(s_syncObjWinOP);

	bool bRet = false;
	if(::OpenClipboard(NULL))
	{
		::EmptyClipboard();
		HGLOBAL clipbuffer;
		char *buffer;
		int size = (in_buf.length() + 1) * 2;
		clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, size);
		buffer = (char *)::GlobalLock(clipbuffer);
		strcpy_s(buffer, size, in_buf.c_str());
		::GlobalUnlock(clipbuffer);
		::SetClipboardData(CF_TEXT, clipbuffer);
		::CloseClipboard();
		bRet = true;
	}
	return bRet;
}

bool getClipboard(std::string & out_buf)
{
	DAutoSync sync(s_syncObjWinOP);

	bool bRet = false;
	if(::OpenClipboard(NULL))
	{
		//��ü���������
		HGLOBAL hMem = GetClipboardData(CF_UNICODETEXT);
		if(NULL != hMem)
		{
			wchar_t* lpStrW = (wchar_t*)::GlobalLock(hMem); 
			int lenWCS = lstrlenW(lpStrW);
			int lenMBS = lenWCS*2;
			char * lpStr = new char[lenMBS];
			memset(lpStr, 0, lenMBS);
			int iCvt = DStr::WinWcsToMbs(lpStrW,lenWCS,lpStr,lenMBS);
			if (iCvt >= 0 && NULL!= lpStr)
			{
				//printf("%s",lpStr);
				out_buf.assign(lpStr, strlen(lpStr));
				bRet = true;
			}
			delete[] lpStr;
			::GlobalUnlock(hMem);
		}
		else
		{
			// ���а��
			out_buf.assign("", strlen(""));
			bRet = true;
		}
		::CloseClipboard();
	}
	return bRet;
}

bool clearClipboard()
{
	DAutoSync sync(s_syncObjWinOP);

	bool bRet = false;
	if(::OpenClipboard(NULL))
	{
		if (TRUE == ::EmptyClipboard())
		{
			bRet = true;
		}
		::CloseClipboard();
	}
	return bRet;
}

bool getCtrlVFormWin(HWND hWnd,std::string & out_buf)
{
	DAutoSync sync(s_syncObjWinOP);

	// ������а���������
	std::string buf_save;
	bool bBufSaved = false;
	for (int i=0; i<5; i++)
	{
		if (getClipboard(buf_save))
		{
			if (clearClipboard())
			{
				bBufSaved = true;
				break;
			}
		}
	}

	// ���ݿ��������а�
	std::string buf;
	bool bBufCopied = false;
	if (bBufSaved)
	{
		for (size_t i = 0; i < 5; i++)
		{
			if (isAvailableClipboard())
			{
				//ͨ��spy++���߽ػ񴰿��¼���ȡ
				::SendMessage(hWnd, WM_COMMAND, 0x0000E122, 0x00000000);

				// Ӳ�Է����¼����˷������ã�����Զ������رպ�keybd_eventʧЧ
				//Sleep(30);
				//keybd_event(VK_CONTROL, (BYTE)0, 0, 0);
				//Sleep(5);
				//::SendMessage(hWnd, WM_KEYDOWN, 'C', MapVirtualKey('C', 0));
				//Sleep(5);
				//::SendMessage(hWnd, WM_KEYUP, 'C', MapVirtualKey('C', 0));
				//Sleep(5);
				//keybd_event(VK_CONTROL, (BYTE)0, KEYEVENTF_KEYUP, 0);
				//Sleep(10);

				if (getClipboard(buf) && buf.size() > 0)
				{
					bBufCopied = true;
					break;
				}
			}
		}
	}

	// �ָ����а�ԭ������
	bool bRecoverd = false;
	if(bBufSaved)
	{
		for (int i=0; i<5; i++)
		{
			if (setClipboard(buf_save))
			{
				bRecoverd = true;
				break;
			}
		}
	}

	// ������������
	if(bBufCopied)
	{
		out_buf.assign(buf);
		return true;
	}

	return false;
}