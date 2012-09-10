<?php
$this->breadcrumbs=array(
	'Classroom Basic Infos'=>array('index'),
	$model->id,
);

$this->menu=array(
	array('label'=>yii::t('courseArrangement', 'View Classroom'), 'url'=>array('index')),
	array('label'=>yii::t('courseArrangement', 'Create Classroom'), 'url'=>array('create')),
	array('label'=>yii::t('courseArrangement', 'Manage Classroom'), 'url'=>array('admin')),
);
?>



</script>
<h1>View ClassroomBasicInfo #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'room_number',
		'location',
		'campus',
		'type',
		'capacity',
		'college',
	),
)); ?>
