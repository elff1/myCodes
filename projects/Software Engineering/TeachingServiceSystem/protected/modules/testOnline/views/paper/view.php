<?php
$this->breadcrumbs=array(
	'Online Test Subsystem'=>array('/testOnline'),
	'Paper Bank'=>array('paperBank/'),
//	'Papers'=>array('index'),
	$model->id,
);

$this->menu=array(
	array('label'=>'List Paper', 'url'=>array('index')),
	array('label'=>'Create Paper', 'url'=>array('create')),
	array('label'=>'Update Paper', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete Paper', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage Paper', 'url'=>array('admin')),
);
?>

<h1>View Paper #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'paper_id',
		'pro_id',
		'pro_score',
	),
)); ?>
