package gl.NovelFrame;
import gl.MyNovel.MyNovel;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Vector;


import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;



class MyNovelFrame extends JFrame
{	

	public MyNovelFrame(String title)
	{
		
		super(title);
		
		jbInit();
	}
	
	private JTextField txtAddress=null;
	private JButton btnSearch=null;
	private JList list=null;
	private JButton btnDownloadAll=null;
	private JTextArea txtContent=null;
	private Vector listContent=null;
	private Vector vcURL=null;
	private MyNovel myNovel=null;
	private void jbInit()
	{
		this.setLayout(new BorderLayout());
		//3 panels...
		JPanel topPan = new JPanel();
		topPan.setBackground(Color.WHITE);
		topPan.setBorder(BorderFactory.createEtchedBorder());
		JPanel contentPan = new JPanel();
		contentPan.setBorder(BorderFactory.createEtchedBorder());
		JPanel leftPan = new JPanel();
		leftPan.setBorder(BorderFactory.createEtchedBorder());
		
		//top panel
		topPan.setLayout(new GridBagLayout());
		txtAddress=new JTextField("http://www.guoxue.com/minqingstory/sgyy/sgyy.htm",40);
		JLabel lblAddress=new JLabel("请输入小说地址");
		btnSearch=new JButton("搜索");
		topPan.add(lblAddress,new GridBagConstraints(0,0, 1, 1, 0.0, 0.0,
				GridBagConstraints.WEST, GridBagConstraints.NONE,
				new Insets(5, 5, 0, 0), 0, 0));
		topPan.add(txtAddress,new GridBagConstraints(1,0, 1, 1, 1.0, 0.0,
				GridBagConstraints.WEST, GridBagConstraints.HORIZONTAL,
				new Insets(5, 5, 0, 0), 0, 0));
		topPan.add(btnSearch,new GridBagConstraints(2,0, 1, 1, 0.0, 0.0,
				GridBagConstraints.EAST, GridBagConstraints.NONE,
				new Insets(5, 20, 0, 0), 0, 0));
		
		//left panel
		list=new JList();
		JLabel lblLabel=new JLabel("请选择章节");
		btnDownloadAll=new JButton("下载全部");
		
		ArrayList aList=new ArrayList();

		list.setFont(new java.awt.Font("MonoSpaced", 0, 12));
		list.setListData(aList.toArray());
		JScrollPane jScrollPane=new JScrollPane(list,ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED,ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		jScrollPane.setMinimumSize(new Dimension(50,0));
		leftPan.setLayout(new GridBagLayout());
		leftPan.add(lblLabel, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0,
				GridBagConstraints.NORTH, GridBagConstraints.HORIZONTAL,
				new Insets(5, 5, 0, 0), 0, 0));
		leftPan.add(jScrollPane, new GridBagConstraints(0, 1, 1, 1, 0.0, 1.0,
				GridBagConstraints.CENTER, GridBagConstraints.VERTICAL,
				new Insets(5, 5, 0, 0), 0, 0));
		
		leftPan.add(btnDownloadAll, new GridBagConstraints(0, 2, 1, 1, 0.0, 0.0,
				GridBagConstraints.EAST, GridBagConstraints.VERTICAL,
				new Insets(5, 5, 0, 0), 0, 0));
		//jScrollPane.setPreferredSize(new Dimension(100,500));
		
		//center panel
		//JTextArea txtContent=new JTextArea();
		contentPan.setLayout(new GridBagLayout());
		txtContent = new JTextArea();
		txtContent.setBackground(SystemColor.control);
	    txtContent.setFont(new java.awt.Font("MonoSpaced", 0, 15));
	    txtContent.setForeground(new Color(104, 180, 50));
	    txtContent.setBorder(BorderFactory.createLoweredBevelBorder());         
	    txtContent.setCaretColor(Color.black);
	    txtContent.setEditable(true);
	    txtContent.setMargin(new Insets(0, 0, 0, 0));
	    txtContent.setSelectedTextColor(Color.white);
	    txtContent.setSelectionEnd(0);
	    txtContent.setEditable(false);
	    txtContent.setLineWrap(true);//设置自动换行,自动换行则不会出现横向的滚动条
	    
	    String intro="请输入某一小说网址的主页进行搜索，可用网址如：\n";
	    intro+="http://www.guoxue.com/minqingstory/ylh/ylh.htm\n";
	    intro+="http://www.guoxue.com/minqingstory/rlws/rlwsml.htm\n";
	    intro+="http://www.guoxue.com/minqingstory/FSYY/fsyyml.htm\n";
	    intro+="http://www.guoxue.com/minqingstory/sgyy/sgyy.htm\n";
	    txtContent.setText(intro);
	    this.getContentPane().add(txtContent);	    
	    
	    JScrollPane textPane = new JScrollPane(txtContent);
	    this.getContentPane().add(textPane);
	    textPane.setVerticalScrollBarPolicy (JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED); 
		contentPan.add(textPane,new GridBagConstraints(0,0, 1, 1, 1.0, 1.0,
				GridBagConstraints.SOUTHEAST, GridBagConstraints.BOTH,
				new Insets(5, 5, 0, 0), 0, 0));
		
		this.add(topPan, BorderLayout.NORTH);		
		this.add(contentPan, BorderLayout.CENTER);
		this.add(leftPan, BorderLayout.WEST);
		
		//绑定事件
		btnDownloadAll.addActionListener(new MyBtnDownloadAll());
		btnSearch.addActionListener(new MyBtnSearch());
		list.addMouseListener(new MyListClickAdapter());
		
	}
	
	class MyDownloadListThread extends Thread
	{

		public void run() {
			// TODO Auto-generated method stub
			if(vcURL==null) return;
			int m=list.getSelectedIndex();
			System.out.println(m);
			txtContent.setText(myNovel.getContentFromUrl(vcURL.elementAt(list.getSelectedIndex()).toString()));
			txtContent.setCaretPosition(0);
			super.run();
		}
		
	}
	class   MyListClickAdapter   extends   MouseAdapter
	{

		public void mouseClicked(MouseEvent e) {
			// TODO Auto-generated method stub
			if((e.getButton()   ==   MouseEvent.BUTTON1)   &&   (e.getClickCount()   ==   1)) 
	        { 
				MyDownloadListThread listThread=new MyDownloadListThread();
				listThread.start();
				txtContent.setText("下载中，请稍候。。。");
	        }
			super.mouseClicked(e);
		}
		
	}
	public class MyDownloadThread implements Runnable{   
	    public void run(){   
	    	if(vcURL==null)return;
			
			myNovel.WriteTofiles(vcURL,myNovel.novelName+".txt");
			JOptionPane.showMessageDialog(null, myNovel.novelName+"下载已经完成");
			btnDownloadAll.setEnabled(true);
			btnDownloadAll.setText("下载全部");
	    }    
	}
	class MyBtnDownloadAll implements ActionListener
	{

		public void actionPerformed(ActionEvent arg0) {
			MyDownloadThread down=new MyDownloadThread();
			Thread downThread=new Thread(down);
			downThread.start();
			btnDownloadAll.setText("下载中。。");
			btnDownloadAll.setEnabled(false);
		}
		
	}
	class MySearchThread implements Runnable
	{

		public void run() {
			// TODO Auto-generated method stub
			String url=txtAddress.getText();
			String url0=url.substring(0,url.lastIndexOf("/")+1);
			String url1=url.substring(url.lastIndexOf("/")+1);
			myNovel=new MyNovel(url0,url1);
			
			//vcURL.clear();
			vcURL=myNovel.getVectorFromReg(myNovel.strFrontName+"_\\d*\\.htm");
			
			//listContent.clear();
			listContent=myNovel.getVectorFromReg("第.*[\u4e00-\u9fa5]");
			list.setListData(listContent);
			btnSearch.setEnabled(true);
			btnSearch.setText("搜索");
		}
		
	}
	class MyBtnSearch implements ActionListener
	{

		public void actionPerformed(ActionEvent arg0) {
			
			//myNovel.WriteTofiles(vcURL, "三国.txt");
			MySearchThread search=new MySearchThread();
			Thread searchThread=new Thread(search);
			searchThread.start();
			btnSearch.setEnabled(false);
			btnSearch.setText("搜索中。。");
		}
		
	}
}
public class newFrame {
 
 public static void main(String[] args) {
	 try
		{
		 MyNovelFrame example = new MyNovelFrame("亮哥小说阅读器");
			example.setMinimumSize(new Dimension(200,320));
			example.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
			example.pack();
			example.setVisible(true);
			
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
}
}