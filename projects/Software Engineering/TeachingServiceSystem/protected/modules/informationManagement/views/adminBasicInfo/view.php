<?php
$this->breadcrumbs=array(
	'Admin Basic Infos'=>array('index'),
	$model->id,
);
//右侧菜单栏
$this->menu=array(
	array('label'=>'List AdminBasicInfo', 'url'=>array('index')),
	array('label'=>'Create AdminBasicInfo', 'url'=>array('create')),
	array('label'=>'Update AdminBasicInfo', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete AdminBasicInfo', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage AdminBasicInfo', 'url'=>array('admin')),
);
?>

<h1>View AdminBasicInfo #<?php echo $model->id; ?></h1>

<?php 
//显示数据表格的widget
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'admin_id',
		'personal_info_id',
	),
)); ?>
