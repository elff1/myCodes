package gl.MyNovel;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.Vector;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MyNovel {
	public String strUrl;
	public String strName;
	public String novelName;
	public String strFrontName;
	public MyNovel(String url,String name)
	{
		strUrl=url;
		strName=name;
		novelName=strName.substring(0,strName.indexOf("."));
		String temp=strUrl.substring(0,strUrl.lastIndexOf("/"));
		strFrontName=temp.substring(temp.lastIndexOf("/")+1);
	}
	public  Vector getVectorFromReg(String pt)
	{
		Vector vcURL=new Vector();
		URL url = null;
		
		try {
			url = new URL(strUrl+strName);
		
		
			//connection = url.openConnection();
			//connection.setConnectTimeout(10000);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		//DataInputStream dis = null;
		BufferedReader in=null;
		try {
			
			in=new BufferedReader(new InputStreamReader(url.openStream(),"gbk"));
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
		do{
			
			String str=in.readLine();
			if(str==null) break;
			Pattern p=Pattern.compile(pt,Pattern.CASE_INSENSITIVE);
			
		     
			Matcher m=p.matcher(str);
			if(m.find())
			{
				String sTempString=m.group(0);
				vcURL.add(sTempString);
			}
			
		}while(true);

		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
		return vcURL;
	}
	public  void  WriteTofiles(Vector vcURL,String fn) {
		File fl=null;
		
		FileOutputStream fos=null;
		try{
			
			fl=new File(fn);
			fos=new FileOutputStream(fl);
		for (int i = 0; i < vcURL.size(); i++) {
			String strContent=getContentFromUrl(vcURL.elementAt(i).toString());
			fos.write(strContent.getBytes());
		}
		}catch (Exception e) {
			e.printStackTrace();// TODO: handle exception
		}
		try {
			fos.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	public String getContentFromUrl(String url)
	{
		BufferedReader in=null;   
		URL url0=null;
		try {			
		url0=new URL(strUrl+url);
		in   =new BufferedReader(new InputStreamReader(url0.openStream(),"gbk"));
		} catch (Exception e) {
					// TODO: handle exception
				}
		StringBuilder sb=new StringBuilder();
		while(true)
		{
			try {
				String str=in.readLine();
				if(str==null) break;
				sb.append(str);
				
			} catch (Exception e) {
				break;
			}			
		}
		String strContent=sb.toString();
		Pattern p=Pattern.compile("\\<td.*?td\\>");
		Matcher m=p.matcher(strContent);
		
		if(m.find(1))
		{
			strContent=m.group();
		}
		strContent=strContent.replaceAll("\\<.*?\\>", "");
		strContent=strContent.replaceAll("(&nbsp;)+", "\r\n\t");
		return strContent;
		//System.out.println(strContent);
	
	}
	
}
