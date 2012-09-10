<?php
$this->breadcrumbs=array(
	'Student Achievements'=>array('index'),
	$model->id,
);

$this->menu=array(
	array('label'=>'List StudentAchievement', 'url'=>array('index')),
	array('label'=>'Create StudentAchievement', 'url'=>array('create')),
	array('label'=>'Update StudentAchievement', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete StudentAchievement', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage StudentAchievement', 'url'=>array('admin')),
);
?>

<h1>View StudentAchievement #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'gpa_major',
		'gpa_total',
		'credit_total',
		'credit_achieve',
		'credit_major_total',
		'credit_major_achieve',
	),
)); ?>
