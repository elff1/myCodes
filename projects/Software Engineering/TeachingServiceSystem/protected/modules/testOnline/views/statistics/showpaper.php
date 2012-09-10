<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Statistics Analysis'=>array('index'),
		'Show Papers',
);


$this->menu=array(
	array('label'=>TestOnlineModule::t('core','Statistics Analysis of Questions'), 'url'=>array('showprob&id=')),
//	array('label'=>TestOnlineModule::t('core','Statistics Analysis of Paper'), 'url'=>array('showpaper')),
//	array('label'=>'显示学生分析', 'url'=>array('showstu')),
//	array('label'=>'Create statistics', 'url'=>array('create')),
//	array('label'=>'Manage statistics', 'url'=>array('admin')),
	//用于列表显示内容
);
?>

<h1>Show papers</h1>
<?php
    // 显示paper试卷列表
    $this->widget('zii.widgets.grid.CGridView', array(
	'dataProvider'=>PaperBankController::getPapers(),
	'columns'=>array(
    	'id',
		'teacher_id',
		'course_id',
		'is_publish',
		'timelimit',

		array('class'=>'CButtonColumn', 'template'=>'{view}',
			'buttons'=>array(
				'view' => array(
					'url'=>'Yii::app()->createUrl("testOnline/statistics/showprob",array("id"=>end(CHtml::listData(PaperBank::model()->findAllByAttributes(array("id"=>$data->id)),"id","id"))))',
				),
			),
		),
	),
));?>
