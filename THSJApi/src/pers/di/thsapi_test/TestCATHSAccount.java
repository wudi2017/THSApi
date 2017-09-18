package pers.di.thsapi_test;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Formatter;
import java.util.List;

import pers.di.thsapi.*;
import pers.di.thsapi.THSApi.*;

public class TestCATHSAccount {

	// for test: please be carefull
	public static void main(String[] args) {
        // TODO Auto-generated method stub
        //System.getProperty("java.library.path");
		Formatter fmt = new Formatter(System.out);
		fmt.format("### main begin\n");
		
		// ��ʼ������
		{
			int iInitRet = THSApi.initialize();
	        fmt.format("CATHSAccount.initialize err(%d)\n", iInitRet);
		}
        
		// �����ʽ����
		{
			ObjectContainer<Float> container = new ObjectContainer<Float>();
	        int ret = THSApi.getAvailableMoney(container);
	        fmt.format("CATHSAccount.getAvailableMoney err(%d) AvailableMoney(%.2f)\n", ret, container.get());
		}

		// ���ʲ�����
		{
			ObjectContainer<Float> container = new ObjectContainer<Float>();
	        int ret =  THSApi.getTotalAssets(container);
	        fmt.format("CATHSAccount.getTotalAssets err(%d) TotalAssets(%.2f)\n", ret, container.get());
		}

		// ���й�Ʊ����ֵ����
		{
			ObjectContainer<Float> container = new ObjectContainer<Float>();
	        int ret =  THSApi.getAllStockMarketValue(container);
	        fmt.format("CATHSAccount.getAllStockMarketValue err(%d) AllStockMarketValue(%.2f)\n", ret, container.get());
		}

		// �ֹ��б����
		{
			List<THSHoldStock> container = new ArrayList<THSHoldStock>();
	        int ret = THSApi.getHoldStockList(container);
	        fmt.format("CATHSAccount.getHoldStockList err(%d) resultList size(%d)\n", ret, container.size());
	        for(int i=0;i<container.size();i++)
	        {
	        	THSHoldStock cHoldStock = container.get(i);
	        	fmt.format("    {%s %d %d %.3f %.3f %.3f}\n", cHoldStock.stockID, cHoldStock.totalAmount, cHoldStock.availableAmount,
	        			cHoldStock.refProfitLoss, cHoldStock.refPrimeCostPrice, cHoldStock.curPrice);
	        }
		}
        
		// ����ί�в���
		{
	        //int iBuyRet = CATHSAccount.buyStock("601988", 100, 0.07f);
	        //fmt.format("CATHSAccount.buyStock err(%d)\n", iBuyRet);
		}
        
		// ����ί�в���
		{
	        //int iSellRet = CATHSAccount.sellStock("601988", 100, 190.7f);
	        //fmt.format("CATHSAccount.sellStock err(%d)\n", iSellRet);
		}
		
		// test loop
		{
			long testtimes = Long.MAX_VALUE;
			for(int m=0; m<testtimes; m++)
			{
				
				SimpleDateFormat sdf =new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
				String datetime = sdf.format(new Date());
				
				fmt.format("\n[%s] CATHSAccount testing times(%s) ==================>>>>\n", datetime, m);
				
				{
					ObjectContainer<Float> container = new ObjectContainer<Float>();
			        int ret = THSApi.getAvailableMoney(container);
			        fmt.format("CATHSAccount.getAvailableMoney err(%d) AvailableMoney(%.2f)\n", ret, container.get());
				}

				{
					ObjectContainer<Float> container = new ObjectContainer<Float>();
			        int ret =  THSApi.getTotalAssets(container);
			        fmt.format("CATHSAccount.getTotalAssets err(%d) TotalAssets(%.2f)\n", ret, container.get());
				}
				
				{
					ObjectContainer<Float> container = new ObjectContainer<Float>();
			        int ret =  THSApi.getAllStockMarketValue(container);
			        fmt.format("CATHSAccount.getAllStockMarketValue err(%d) AllStockMarketValue(%.2f)\n", ret, container.get());
				}
				
				{
					List<THSHoldStock> container = new ArrayList<THSHoldStock>();
			        int ret = THSApi.getHoldStockList(container);
			        fmt.format("CATHSAccount.getHoldStockList err(%d) resultList size(%d)\n", ret, container.size());
			        for(int i=0;i<container.size();i++)
			        {
			        	THSHoldStock cHoldStock = container.get(i);
			        	fmt.format("    {%s %d %d %.3f %.3f %.3f}\n", cHoldStock.stockID, cHoldStock.totalAmount, cHoldStock.availableAmount,
			        			cHoldStock.refProfitLoss, cHoldStock.refPrimeCostPrice, cHoldStock.curPrice);
			        }
				}
		        
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}

        fmt.format("### main end\n");
    }
}
