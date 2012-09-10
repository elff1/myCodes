<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Student Online Test' => array (
				'index' 
		),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);

$this->menu=array(
	array('label'=>'List TestRecording', 'url'=>array('index')),
	array('label'=>'Create TestRecording', 'url'=>array('create')),
	array('label'=>'View TestRecording', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage TestRecording', 'url'=>array('admin')),
);
?>

<h1>Update TestRecording <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>