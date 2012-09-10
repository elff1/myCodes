<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Statistics Analysis'=>array('index'),
		'show students',
		// 此页面用于展示当希望统计比例的题目从未做过的时候出现的页面
);

$this->menu=array(
	array('label'=>'显示题目分析', 'url'=>array('showprob&id=')),
	array('label'=>'显示试卷分析', 'url'=>array('showpaper')),
	array('label'=>'显示学生分析', 'url'=>array('showstu')),
	array('label'=>'Create statistics', 'url'=>array('create')),
	array('label'=>'Manage statistics', 'url'=>array('admin')),);
	//用于列表显示内容
?>

<h1>这个题目还从来没有人做过，返回吧少年</h1>
