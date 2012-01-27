import java.net.*;
import java.util.ArrayList;
import java.util.Vector;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.awt.List;
import java.io.*;

class WebGrab {
	String url;
	public WebGrab() {
		// TODO Auto-generated constructor stub
		url="http://www.baidu.com/";
	}
	public WebGrab(String u) {
		// TODO Auto-generated constructor stub
		url=u;
	}
	private String getSource(){
		String temp=new String();
		try{
				URL sourceURL=
					new URL(url); 
				BufferedReader in=new BufferedReader(
								new InputStreamReader(sourceURL.openStream()
										));
				StringBuffer sbBuffer=new StringBuffer();
				while((temp=in.readLine())!=null){
					sbBuffer.append(temp);
					sbBuffer.append("\r\n");
				}
				temp=	sbBuffer.toString();
				in.close();
		
		}catch (Exception e) {
			System.out.println("Error URL:\n"+e);	
		}
		return temp;
	}
	
	public String outTag(String s)  
    {  
		return  s.replaceAll("<.*?>", "");
    } 
	
	public String getText(String html){  
        String text = "";    
		/*System.out.println(htmlSource);
        Vector<String> list = new Vector<String>();  
        Pattern pa = Pattern.compile("<pre(.*?)>[.\\s]*</pre>");//源码中正文正则表达式  
        Matcher ma = pa.matcher(htmlSource);  
        while (ma.find())//寻找符合el的字串  
        {  
            list.add(ma.group());//将符合el的字串加入到list中  
        }  
        
        System.out.println(list.size());
        
        for (int i = 0; i < list.size(); i++)  
        {  
        	String temp=list.get(i);
            text = text + "    "+temp.substring(temp.indexOf('>')+1,
            		temp.indexOf("</pre>")-1);  
            //text=text+"\r\n";
        }  */

        text = html.substring(html.indexOf('>', html.indexOf("<pre"))+2, 
        		html.indexOf("</pre>")-1);
        return text;  
    }  

	public Vector<String> getTitle(String htmlSource){  
        Vector<String> list = new Vector<String>();  
        String title = "";    
        Pattern pa = Pattern.compile("blank>.*?</a><BR>");//源码中标题正则表达式  
        Matcher ma = pa.matcher(htmlSource);  
        while (ma.find())//寻找符合el的字串  
        {  
        	title = ma.group();
        	title = title.substring(6,title.length()-8);
            list.add(title);//将符合el的字串加入到list中  
        }
        return list;
    }  
	
	public Vector<String> getLinks(String htmlSource){  
        Vector<String> list = new Vector<String>();  
        String temp = "";    
        //Pattern pa = Pattern.compile("<a\\s+href=\"SGYY_[0-9][0-9][0-9].htm\"");//源码中超链接正则表达式
        Pattern pa = Pattern.compile("href=\"http://.*?.htm\"");
        Matcher ma = pa.matcher(htmlSource);  
        while (ma.find())//寻找符合el的字串  
        {  
        	temp=ma.group();
        	temp=temp.substring(temp.indexOf('\"')+1,temp.length()-1);
        	//temp="http://www.guoxue.com/minqingstory/sgyy/"+temp;
            list.add(temp);//将符合el的字串加入到list中  
        }  
        return list;  
    }  
	
	public  void getLinksContent(Vector<String> title, Vector<String> list) { 
		//String u3 = "http://read.pudn.com/downloads4/sourcecode/database/15158/AnalyseWords.cpp__.htm";
		//String title = "AnalyseWords.cpp";
		String source;
		String content="";
		for(int i=0;i<list.size();i++){
			System.out.println(title.get(i));
			System.out.println(list.get(i));
			WebGrab web=new WebGrab(list.get(i));
			source = web.getSource();
			content=content+web.getText(source);
			
			try{
				FileOutputStream out=new FileOutputStream(
						new File(title.get(i)));
				out.write(content.getBytes());
			}
			catch (Exception e) {
				// TODO: handle exception
				System.out.println("Error URL:\n"+e);
			}
		}
    } 
	
	public static void main(String[] args) {
		String u1 = "http://www.guoxue.com/minqingstory/sgyy/sgyy.htm";
		String u2 = "http://www.pudn.com/downloads4/sourcecode/database/detail15158.html";
		
		WebGrab wWebGrab =new WebGrab(u2);
		//wWebGrab.getLinksContent(wWebGrab.getLinks(wWebGrab.getSource()));
		
		String source = wWebGrab.getSource();
		Vector<String> title = wWebGrab.getTitle(source);
		Vector<String> list = wWebGrab.getLinks(source);
		/*for(int i=0;i<list.size();i++){
			System.out.println(title.get(i));
			System.out.println(list.get(i));
		}
		System.out.printf("%d %d\n", title.size(), list.size());*/
		
		wWebGrab.getLinksContent(title, list);
	}
}