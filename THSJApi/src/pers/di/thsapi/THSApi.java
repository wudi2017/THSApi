package pers.di.thsapi;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Formatter;
import java.util.List;
import java.util.Properties;

/*
 * http://blog.csdn.net/qinjuning/article/details/7607214
 * http://blog.csdn.net/buleriver/article/details/26577895
 * 
 * ǩ���鿴��
 * http://blog.csdn.net/qq_17387361/article/details/52701481
 * ��bin�£�ִ�� javap -s stormstock.ori.capi.CATHSAccount
 * 
 * jni��C++�ļ�����
 * �ڴ���src��,ִ�� javah stormstock.ori.capi.CATHSAccount
 */
 
public class THSApi {
	
	static{
		// add libpath
		String yourPath = "lib";
		System.setProperty("java.library.path", yourPath);
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
		String libraryName = "thscapi";
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
		public String stockID; // ��ƱID
		public int totalAmount; // �����������ɣ�
		public int availableAmount; // ��������
		public float refProfitLoss; // �ο�ӯ��
		public float refPrimeCostPrice; // �ο��ɱ���
		public float curPrice; // ��ǰ��
	}
	
	
	/*
	 * TongHuaShun Initialize
	 * ͬ��˳��ʼ��
	 * return ErrorCode
	 * 0 �ɹ�
	 */
	public static native int initialize();
	
	/*
	 * getAvailableMoney
	 * ��ȡ�����ʽ�
	 */
	public static native int getAvailableMoney(ObjectContainer<Float> availableMoney);
	
	/*
	 * getTotalAssets
	 * ��ȡ���ʲ�
	 */
	public static native int getTotalAssets(ObjectContainer<Float> totalAssets);
	
	/*
	 * getAllStockMarketValue
	 * ��ȡ��Ʊ����ֵ
	 */
	public static native int getAllStockMarketValue(ObjectContainer<Float> allStockMarketValue);
	
	/*
	 * getHoldStockList
	 * ��ȡ�ֹ��б�
	 */
	public static native int getHoldStockList(List<HoldStock> container);
	
	/*
	 * buyStock
	 * ί�������µ�
	 * return ErrorCode
	 * 0 �ɹ�
	 */
	public static native int buyStock(String stockId, int amount, float price);
	
	/*
	 * buyStock
	 * ί�������µ�
	 * return ErrorCode
	 * 0 �ɹ�
	 */
	public static native int sellStock(String stockId, int amount, float price);
}
