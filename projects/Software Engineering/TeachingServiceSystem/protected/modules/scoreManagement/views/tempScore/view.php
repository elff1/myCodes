<?php
$this->breadcrumbs=array(
	'Temp Scores'=>array('index'),
	$model->id,
);

$this->menu=array(
	array('label'=>'List TempScore', 'url'=>array('index')),
	array('label'=>'Create TempScore', 'url'=>array('create')),
	array('label'=>'Update TempScore', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete TempScore', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage TempScore', 'url'=>array('admin')),
);
?>

<h1>View TempScore #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'student_id',
		'teacher_id',
		'teachingclass_id',
		'score',
	),
)); ?>
