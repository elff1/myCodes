<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Statistics',
);

$this->menu=array(
	array('label'=>TestOnlineModule::t('core','Statistics Analysis of Questions'), 'url'=>array('showprob&id=')),
	array('label'=>TestOnlineModule::t('core','Statistics Analysis of Paper'), 'url'=>array('showpaper')),
//	array('label'=>'显示学生分析', 'url'=>array('showstu')),
//	array('label'=>'Create statistics', 'url'=>array('create')),
//	array('label'=>'Manage statistics', 'url'=>array('admin')),
	//用于列表显示内容
	);
?>
<h1>Statistics</h1>
Welcome to the statistics page, please choose an operation you want.
