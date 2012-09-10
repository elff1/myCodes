<?php
$this->breadcrumbs=array(
	'Exams'=>array('index'),
	$model->id,
);

$this->menu=array(
	array('label'=>'List Exam', 'url'=>array('index')),
	array('label'=>'Create Exam', 'url'=>array('create')),
	array('label'=>'Update Exam', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete Exam', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage Exam', 'url'=>array('admin')),
);
?>

<h1>View Exam #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'class_id',
		'classroom_id',
		'teacher1_id',
		'teacher2_id',
		'exam_time',
	),
)); ?>
