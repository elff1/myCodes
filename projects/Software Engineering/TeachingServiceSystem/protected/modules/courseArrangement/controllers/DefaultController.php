<?php

class DefaultController extends Controller
{
	public function actionIndex()
	{
		$this->render('index');
	}
	
	public function filters()
	{
		return array(
			'rights', // perform access control for CRUD operations
		);
	}
	
	public function actionAjax()
	{
		set_time_limit(0); 
		if(Yii::app()->request->isAjaxRequest)
		{
			$statefilename="C:/myphp/root/red/TeachingServiceSystem/busy";
			$state=1;
			if(!file_exists($statefilename)){
				$state=1;
			}
			else{
				$state=0;
			}
			if($state==1){			
				$path = "C:/myphp/root/red/TeachingServiceSystem/";
				if(!is_dir($path))
				{
					mkdir($path);
				}
				//得到课程信息
		//		$filename= $path."teachingclassID";
				$filename= $path."class";
				$fp=fopen("$filename", "w+"); //打开文件指针，创建文件
				
				$classes = ClassTeacher::model()->findAllBySql("select *from class_teacher order by teacherid",array());
				
				$countT = ClassTeacher::model()->findAllBySql("select distinct teacherid from class_teacher",array());
	
				$col = count($countT)."\n";
				fwrite($fp, $col, strlen($col)); //插入一条记录 
				foreach($classes as $class)
				{
					//echo "ok\n";
					$teachingclasses = TeachingclassInfo::model()->findAllByPK($class->classid);
					$course =CourseBasicInfo::model()->findAllByAttributes(array('id'=>$teachingclasses[0]->course_num));
					
					$temp=$course[0]->credit;
					if($temp=="")
						$temp=-1;
					$col =$class->teacherid." ".$class->classid." ".$temp."\n";//." ".$teachingclasses[0]->max."\n";//记录赋值 
					fwrite($fp, $col, strlen($col)); //插入一条记录 
				}
				fclose($fp); //关闭文件 
			
				//得到教室id capacity
				$filename2= $path."classroom";
				$fp2=fopen("$filename2", "w+"); //打开文件指针，创建文件
				$classroom = ClassroomBasicInfo::model()->findAllBySql("select id,capacity from classroom_basic_info",array());
				foreach($classroom as $clr){
					$col = $clr->id." "."\n";//$clr->capacity."\n";
					fwrite($fp2, $col, strlen($col));	
				}
				fclose($fp2); //关闭文件 

				$command = "C:/myphp/root/red/TeachingServiceSystem/run > output.txt";
				//$command = "d:/red/hello.exe";
				system($command);
				echo "排课结束！";
			}
			else{
				echo "正在排课中，请刷新页面";
			}

		}
	}
	public function actionAjaxx()
	{
		set_time_limit(0); 
		if(Yii::app()->request->isAjaxRequest)
		{
			$statefilename="C:/myphp/root/red/TeachingServiceSystem/result";
			if(!file_exists($statefilename)){
				echo "请先进行排课！";
			}
			else{
				ClassTime::model()->deleteAll("",array());
				$fp=fopen("$statefilename","r");
				$fail=0;
				$sucess=0;
			//	echo "hi";
			//	$classtime=new ClassTime;
			//	$classtime->class_id='1';
			//	$classtime->time=1;
			//	$classtime->classroom_id='1';
			//	if($classtime->save()==0){
			//		$flag=0;
			//	}
				while(!feof($fp)){
					$tuple=fgetcsv($fp,100," ");
				//	echo $tuple[0]." ".$tuple[1]." ".$tuple[2]."<br/>";
					if(isset($tuple[0])&&isset($tuple[0])&&isset($tuple[0])){
						$classtime=new ClassTime;
						$classtime->class_id="$tuple[0]";
						$classtime->time=intval($tuple[1]);
						$classtime->classroom_id="$tuple[2]";
						$classtime->isSingle=0;
						if($classtime->save()<=0){
							$fail++;
						}
						else{
							$sucess++;
						}
					}
				}
				fclose($fp);
				unlink("$statefilename");
				echo $sucess."条记录导入成功，".$fail."条记录导入失败。";
			}
		}
	}
}