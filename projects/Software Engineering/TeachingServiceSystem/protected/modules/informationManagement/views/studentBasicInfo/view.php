<?php
$this->breadcrumbs=array(
	'Student Basic Infos'=>array('index'),
	$model->id,
);
//右侧菜单栏
$this->menu=array(
	array('label'=>'List StudentBasicInfo', 'url'=>array('index')),
	array('label'=>'Create StudentBasicInfo', 'url'=>array('create')),
	array('label'=>'Update StudentBasicInfo', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete StudentBasicInfo', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage StudentBasicInfo', 'url'=>array('admin')),
);
?>

<h1>View StudentBasicInfo #<?php echo $model->id; ?></h1>

<?php  
//显示数据表格的widget
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'student_id',
		'current_grade',
		'program_id',
		'entry_date',
		'class_id',
		'remark',
		'personal_info_id',
	),
)); ?>
