<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Question Bank',
);

$this->menu=array(
//	array('label'=>TestOnlineModule::t('core','List Questions'), 'url'=>array('index')),
	array('label'=>TestOnlineModule::t('core','Add Question'), 'url'=>array('create')),
	array('label'=>TestOnlineModule::t('core','Manage Questions'), 'url'=>array('admin')),
	array('label'=>TestOnlineModule::t('core','Batch Add Questions'), 'url'=>array('batchCreate')),
);
?>

<h1>Question Banks</h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'./_view',
)); ?>
