<?php
$this->breadcrumbs=array(
	'Teachingclass Infos'=>array('index'),
	$model->id,
);

$this->menu=array(
	array('label'=>'List TeachingclassInfo', 'url'=>array('index')),
	array('label'=>'Create TeachingclassInfo', 'url'=>array('create')),
	array('label'=>'Update TeachingclassInfo', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete TeachingclassInfo', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage TeachingclassInfo', 'url'=>array('admin')),
);
?>

<h1>View TeachingclassInfo #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'course_num',
		'max',
		'term',
		'campus',
		'dependence',
	),
)); ?>
