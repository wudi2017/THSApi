package pers.di.thsapi;

import java.io.File;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Formatter;
import java.util.List;
import java.util.Properties;

/*
 * http://blog.csdn.net/qinjuning/article/details/7607214
 * http://blog.csdn.net/buleriver/article/details/26577895
 * 
 * 签名查看：
 * http://blog.csdn.net/qq_17387361/article/details/52701481
 * 在bin下，执行 javap -s stormstock.ori.capi.CATHSAccount
 * 
 * jni的C++文件生成
 * 在代码src下,执行 javah stormstock.ori.capi.CATHSAccount
 */
 
public class THSApi {
	
	static{
		// add libpath
		String binPath = THSApi.class.getProtectionDomain().getCodeSource().getLocation().getPath();
		if (binPath.endsWith(".jar")) {// 可执行jar包运行的结果里包含".jar"  
            // 截取路径中的jar包名  
			binPath = binPath.substring(0, binPath.lastIndexOf("/") + 1);  
        }  
		File file = new File(binPath);
		String CurPath = file.getAbsolutePath();
		//System.out.println(CurPath);
		System.setProperty("java.library.path", CurPath);
		Field sysPath = null;
		try {
			sysPath = ClassLoader.class.getDeclaredField("sys_paths");
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		sysPath.setAccessible( true );
		try {
			sysPath.set( null, null );
		} catch (IllegalArgumentException | IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		// load c++ API dll
		String libraryName = "thscapi_x86";
		Properties properties = System.getProperties();
		String jvmName = properties.getProperty("java.vm.name");
		if(jvmName.contains("64"))
		{
			libraryName = "thscapi_x64";
		}
		try {
			sysPath = ClassLoader.class.getDeclaredField("sys_paths");
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		// System.out.println("System.loadLibrary: " + libraryName);
		System.loadLibrary(libraryName);
    }
	
	
	/*
	 * **************************************************************************
	 * public IF define
	 */
	
	public static enum TRANACT {
		BUY,
		SELL,
	}

	
	public static class ObjectContainer<T> {
		public ObjectContainer()
		{
			m_object = null;
		}
		public void set(T obj)
		{
			m_object = obj;
		}
		public T get()
		{
			return m_object;
		}
		public T move()
		{
			T tmp = m_object;
			m_object = null;
			return tmp;
		}
		private T m_object;
	}

	
	public static class HoldStock {
		public String stockID; // 股票ID
		public int totalAmount; // 持有总量（股）
		public int availableAmount; // 可卖数量
		public float refProfitLoss; // 参考盈亏
		public float refPrimeCostPrice; // 参考成本价
		public float curPrice; // 当前价
	}
	
	public static class CommissionOrder {
		public String time; // 时间
		public String stockID; // 股票ID
		public TRANACT tranAct; // 操作
		public int commissionAmount; //委托数量
		public float commissionPrice; //委托价格
		public int dealAmount; // 成交数量
		public float dealPrice; // 成交均价
	}

	public static class DealOrder
	{
		public String time; // 时间
		public String stockID; // 股票ID
		public TRANACT tranAct; // 交易动作
		public int dealAmount; // 成交数量
		public float dealPrice; // 成交均价
	};
	
	/*
	 * TongHuaShun Initialize
	 * 同花顺初始化
	 * return ErrorCode
	 * 0 成功
	 */
	public static native int initialize();
	
	/*
	 * getAvailableMoney
	 * 获取可用资金
	 */
	public static native int getAvailableMoney(ObjectContainer<Float> availableMoney);
	
	/*
	 * getTotalAssets
	 * 获取总资产
	 */
	public static native int getTotalAssets(ObjectContainer<Float> totalAssets);
	
	/*
	 * getAllStockMarketValue
	 * 获取股票总市值
	 */
	public static native int getAllStockMarketValue(ObjectContainer<Float> allStockMarketValue);
	
	/*
	 * getHoldStockList
	 * 获取持股列表
	 */
	public static native int getHoldStockList(List<HoldStock> container);
	
	/*
	 * getCommissionOrderList
	 * 获取委托列表
	 */
	public static native int getCommissionOrderList(List<CommissionOrder> container);
	
	/*
	 * getDealOrderList
	 * 获取成交列表
	 */
	public static native int getDealOrderList(List<DealOrder> container);
	
	/*
	 * buyStock
	 * 委托买入下单
	 * return ErrorCode
	 * 0 成功
	 */
	public static native int buyStock(String stockId, int amount, float price);
	
	/*
	 * buyStock
	 * 委托卖出下单
	 * return ErrorCode
	 * 0 成功
	 */
	public static native int sellStock(String stockId, int amount, float price);
}
