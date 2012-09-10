<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Student Online Test' => array (
				'index' 
		),
	$model->id,
);

$this->menu=array(
	array('label'=>'List TestRecording', 'url'=>array('index')),
	array('label'=>'Create TestRecording', 'url'=>array('create')),
	array('label'=>'Update TestRecording', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete TestRecording', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage TestRecording', 'url'=>array('admin')),
);
?>

<h1>View TestRecording #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'student_id',
		'paper_pro_id',
		'choose',
		'is_commit',
		'score',
	),
)); ?>
