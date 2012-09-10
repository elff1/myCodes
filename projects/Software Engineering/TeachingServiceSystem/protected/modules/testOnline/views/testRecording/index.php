<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Studetn Online Test',
);


$this->menu=array(
	array('label'=>'Create TestRecording', 'url'=>array('create')),
	array('label'=>'Manage TestRecording', 'url'=>array('admin')),
);
?>

<h1><?php echo 'Take a Test Online'; ?></h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
