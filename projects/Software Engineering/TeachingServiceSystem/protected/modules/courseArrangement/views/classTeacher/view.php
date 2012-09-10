<?php
$this->breadcrumbs=array(
	'Class Teachers'=>array('index'),
	$model->id,
);

$this->menu=array(
	array('label'=>'List ClassTeacher', 'url'=>array('index')),
	array('label'=>'Create ClassTeacher', 'url'=>array('create')),
	array('label'=>'Update ClassTeacher', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete ClassTeacher', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage ClassTeacher', 'url'=>array('admin')),
);
?>

<h1>View ClassTeacher #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'teacherid',
		'classid',
	),
)); ?>
