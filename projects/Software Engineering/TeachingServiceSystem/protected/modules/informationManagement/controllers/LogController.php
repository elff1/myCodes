<?php
//log控制器
class LogController extends Controller
{
	public function actionIndex()
	{
		//获取log文件
		$logPath = Yii::getPathOfAlias('application.runtime').'/application.log';
		$file = Yii::app()->file->set($logPath);
		//获取log内容
		$contents = $file->contents;
		//输出
		$this->render('index', array('contents'=>$contents));
	}

	// Uncomment the following methods and override them if needed
	//权限控制，使用rights
	public function filters()
	{
		// return the filter configuration for this controller, e.g.:
		return array(
			'rights',
		);
	}
	/*
	public function actions()
	{
		// return external action classes, e.g.:
		return array(
			'action1'=>'path.to.ActionClass',
			'action2'=>array(
				'class'=>'path.to.AnotherActionClass',
				'propertyName'=>'propertyValue',
			),
		);
	}
	*/
}