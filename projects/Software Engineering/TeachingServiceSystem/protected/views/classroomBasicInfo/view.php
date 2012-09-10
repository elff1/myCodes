<?php
$this->breadcrumbs=array(
	'Classroom Basic Infos'=>array('index'),
	$model->id,
);

$this->menu=array(
	array('label'=>'List ClassroomBasicInfo', 'url'=>array('index')),
	array('label'=>'Create ClassroomBasicInfo', 'url'=>array('create')),
	array('label'=>'Update ClassroomBasicInfo', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete ClassroomBasicInfo', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage ClassroomBasicInfo', 'url'=>array('admin')),
);
?>

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
