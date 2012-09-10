<?php
$this->breadcrumbs=array(
	'Teacher Apps'=>array('index'),
	$model->name,
);

$this->menu=array(
	array('label'=>yii::t('courseArrangement', 'New application'), 'url'=>array('create')),
	array('label'=>yii::t('courseArrangement', 'Quary application'), 'url'=>array('index')),
	array('label'=>yii::t('courseArrangement', 'Confirm application'), 'url'=>array('confirm')),
);
?>

<h1>View TeacherApp #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'preferPlace',
		'preferTime',
		'courseID',
		'name',
		'teacherID',
		'appTime',
	),
)); ?>
