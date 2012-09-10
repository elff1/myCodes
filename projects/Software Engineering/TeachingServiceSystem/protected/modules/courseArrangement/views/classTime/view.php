<?php
$this->breadcrumbs=array(
	'Class Times'=>array('index'),
	$model->id,
);

$this->menu=array(
	array('label'=>Yii::t('courseArrangement','List ClassTime'), 'url'=>array('index')),
	array('label'=>Yii::t('courseArrangement','Create ClassTime'), 'url'=>array('create')),
	array('label'=>Yii::t('courseArrangement','Manage ClassTime'), 'url'=>array('admin')),
);
?>

<h1>View ClassTime #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'class_id',
		'classroom_id',
		'time',
		'isSingle',
	),
)); ?>
