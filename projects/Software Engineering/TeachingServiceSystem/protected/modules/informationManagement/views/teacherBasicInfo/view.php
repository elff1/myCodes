<?php
$this->breadcrumbs=array(
	'Teacher Basic Infos'=>array('index'),
	$model->title,
);
//右侧菜单栏
$this->menu=array(
	array('label'=>'List TeacherBasicInfo', 'url'=>array('index')),
	array('label'=>'Create TeacherBasicInfo', 'url'=>array('create')),
	array('label'=>'Update TeacherBasicInfo', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete TeacherBasicInfo', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage TeacherBasicInfo', 'url'=>array('admin')),
);
?>

<h1>View TeacherBasicInfo #<?php echo $model->id; ?></h1>

<?php  
//显示数据表格的widget
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'teacher_id',
		array(
			'name'=>'title',
			'value'=>$model->title===null?null:$model->titleOptions[$model->title],
		),
		array(
			'name'=>'department_id',
			'value'=>$model->department===null?null:$model->department->name,
		),
		'personal_info_id',
	),
)); ?>
