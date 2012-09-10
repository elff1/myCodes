<?php
$this->breadcrumbs=array(
	'Temp Requests'=>array('index'),
	$model->id,
);

$this->menu=array(
	array('label'=>'List TempRequest', 'url'=>array('index')),
	array('label'=>'Create TempRequest', 'url'=>array('create')),
	array('label'=>'Update TempRequest', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete TempRequest', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage TempRequest', 'url'=>array('admin')),
);
?>

<h1>View TempRequest #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'teacher_id',
		'teachingclass_id',
		'student_id',
		'score',
		'reason',
		'result',
		'is_handle',
		'is_ack',
	),
)); ?>
