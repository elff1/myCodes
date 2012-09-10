<?php
$this->breadcrumbs=array(
	'Class Basic Infos'=>array('index'),
	$model->name,
);
//右侧菜单栏
$this->menu=array(
	array('label'=>'List ClassBasicInfo', 'url'=>array('index')),
	array('label'=>'Create ClassBasicInfo', 'url'=>array('create')),
	array('label'=>'Update ClassBasicInfo', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete ClassBasicInfo', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage ClassBasicInfo', 'url'=>array('admin')),
);
?>

<h1>View ClassBasicInfo #<?php echo $model->id; ?></h1>

<?php  
//显示数据表格的widget
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'name',
		'grade',
		'tutor_id',
	),
)); ?>
