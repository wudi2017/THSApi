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
		
		// 初始化测试
		{
			int iInitRet = THSApi.initialize();
	        fmt.format("CATHSAccount.initialize err(%d)\n", iInitRet);
		}
        
		// 可用资金测试
		{
			ObjectContainer<Float> container = new ObjectContainer<Float>();
	        int ret = THSApi.getAvailableMoney(container);
	        fmt.format("CATHSAccount.getAvailableMoney err(%d) AvailableMoney(%.2f)\n", ret, container.get());
		}

		// 总资产测试
		{
			ObjectContainer<Float> container = new ObjectContainer<Float>();
	        int ret =  THSApi.getTotalAssets(container);
	        fmt.format("CATHSAccount.getTotalAssets err(%d) TotalAssets(%.2f)\n", ret, container.get());
		}

		// 所有股票总市值测试
		{
			ObjectContainer<Float> container = new ObjectContainer<Float>();
	        int ret =  THSApi.getAllStockMarketValue(container);
	        fmt.format("CATHSAccount.getAllStockMarketValue err(%d) AllStockMarketValue(%.2f)\n", ret, container.get());
		}

		// 持股列表测试
		{
			List<HoldStock> container = new ArrayList<HoldStock>();
	        int ret = THSApi.getHoldStockList(container);
	        fmt.format("CATHSAccount.getHoldStockList err(%d) resultList size(%d)\n", ret, container.size());
	        for(int i=0;i<container.size();i++)
	        {
	        	HoldStock cHoldStock = container.get(i);
	        	fmt.format("    {%s %d %d %.3f %.3f %.3f}\n", cHoldStock.stockID, cHoldStock.totalAmount, cHoldStock.availableAmount,
	        			cHoldStock.refProfitLoss, cHoldStock.refPrimeCostPrice, cHoldStock.curPrice);
	        }
		}
		
		// 委托列表测试
		{
			List<CommissionOrder> container = new ArrayList<CommissionOrder>();
	        int ret = THSApi.getCommissionOrderList(container);
	        fmt.format("CATHSAccount.getCommissionOrderList err(%d) resultList size(%d)\n", ret, container.size());
	        for(int i=0;i<container.size();i++)
	        {
	        	CommissionOrder cCommissionOrder = container.get(i);
	        	fmt.format("    {%s %s %s %d %.3f %d %.3f}\n", cCommissionOrder.time, cCommissionOrder.stockID, cCommissionOrder.tranAct.toString(), 
	        			cCommissionOrder.commissionAmount, cCommissionOrder.commissionPrice,
	        			cCommissionOrder.dealAmount, cCommissionOrder.dealPrice);
	        }
		}
		
		// 成交列表测试
		{
			List<DealOrder> container = new ArrayList<DealOrder>();
	        int ret = THSApi.getDealOrderList(container);
	        fmt.format("CATHSAccount.getDealOrderList err(%d) resultList size(%d)\n", ret, container.size());
	        for(int i=0;i<container.size();i++)
	        {
	        	DealOrder cDealOrder = container.get(i);
	        	fmt.format("    {%s %s %s %d %.3f}\n", cDealOrder.time, cDealOrder.stockID, cDealOrder.tranAct.toString(), 
	        			cDealOrder.dealAmount, cDealOrder.dealPrice);
	        }
		}
            
		// 买入委托测试
		{
	        // int iBuyRet = THSApi.buyStock("601988", 100, 0.07f);
	        // fmt.format("CATHSAccount.buyStock err(%d)\n", iBuyRet);
		}
        
		// 卖出委托测试
		{
	        // int iSellRet = THSApi.sellStock("601988", 100, 190.7f);
	        // fmt.format("CATHSAccount.sellStock err(%d)\n", iSellRet);
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
					List<HoldStock> container = new ArrayList<HoldStock>();
			        int ret = THSApi.getHoldStockList(container);
			        fmt.format("CATHSAccount.getHoldStockList err(%d) resultList size(%d)\n", ret, container.size());
			        for(int i=0;i<container.size();i++)
			        {
			        	HoldStock cHoldStock = container.get(i);
			        	fmt.format("    {%s %d %d %.3f %.3f %.3f}\n", cHoldStock.stockID, cHoldStock.totalAmount, cHoldStock.availableAmount,
			        			cHoldStock.refProfitLoss, cHoldStock.refPrimeCostPrice, cHoldStock.curPrice);
			        }
				}
				
				{
					List<CommissionOrder> container = new ArrayList<CommissionOrder>();
			        int ret = THSApi.getCommissionOrderList(container);
			        fmt.format("CATHSAccount.getCommissionOrderList err(%d) resultList size(%d)\n", ret, container.size());
			        for(int i=0;i<container.size();i++)
			        {
			        	CommissionOrder cCommissionOrder = container.get(i);
			        	fmt.format("    {%s %s %s %d %.3f %d %.3f}\n", cCommissionOrder.time, cCommissionOrder.stockID, cCommissionOrder.tranAct.toString(), 
			        			cCommissionOrder.commissionAmount, cCommissionOrder.commissionPrice,
			        			cCommissionOrder.dealAmount, cCommissionOrder.dealPrice);
			        }
				}
				
				{
					List<DealOrder> container = new ArrayList<DealOrder>();
			        int ret = THSApi.getDealOrderList(container);
			        fmt.format("CATHSAccount.getDealOrderList err(%d) resultList size(%d)\n", ret, container.size());
			        for(int i=0;i<container.size();i++)
			        {
			        	DealOrder cDealOrder = container.get(i);
			        	fmt.format("    {%s %s %s %d %.3f}\n", cDealOrder.time, cDealOrder.stockID, cDealOrder.tranAct.toString(), 
			        			cDealOrder.dealAmount, cDealOrder.dealPrice);
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
