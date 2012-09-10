<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Student Online Test' => array (
				'index' 
		),
	'Create',
);

$this->menu=array(
	array('label'=>'List TestRecording', 'url'=>array('index')),
	array('label'=>'Manage TestRecording', 'url'=>array('admin')),
);
?>

<h1>Create TestRecording</h1>

<?php echo $this->renderPartial('CopyOf_form', array('model'=>$model)); ?>