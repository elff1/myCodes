<?php
$this->breadcrumbs=array(
	'Course Basic Infos'=>array('index'),
	$model->name,
);

$this->menu=array(
	array('label'=>'List CourseBasicInfo', 'url'=>array('index')),
	array('label'=>'Create CourseBasicInfo', 'url'=>array('create')),
	array('label'=>'Update CourseBasicInfo', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete CourseBasicInfo', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage CourseBasicInfo', 'url'=>array('admin')),
);
?>

<h1>View CourseBasicInfo #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'course_id',
		'name',
		'credit',
		'class',
		'prerequsite_required',
		'introduction',
		'syllabus',
		'department_id',
		'priority',
	),
)); ?>
