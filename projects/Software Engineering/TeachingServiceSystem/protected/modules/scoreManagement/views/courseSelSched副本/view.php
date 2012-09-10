<?php
$this->breadcrumbs=array(
	'Course Sel Scheds'=>array('index'),
	$model->id,
);

$this->menu=array(
	array('label'=>'List CourseSelSched', 'url'=>array('index')),
	array('label'=>'Create CourseSelSched', 'url'=>array('create')),
	array('label'=>'Update CourseSelSched', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete CourseSelSched', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage CourseSelSched', 'url'=>array('admin')),
);
?>

<h1>View CourseSelSched #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'stu_id',
		'class_id',
		'required',
		'repeated',
		'abandoned',
		'score',
		'year',
		'term',
	),
)); ?>
