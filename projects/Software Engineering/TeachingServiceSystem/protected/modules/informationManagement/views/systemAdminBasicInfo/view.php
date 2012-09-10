<?php
$this->breadcrumbs=array(
	'SystemAdmin Basic Infos'=>array('index'),
	$model->id,
);
//右侧菜单栏
$this->menu=array(
	array('label'=>'List SystemAdminBasicInfo', 'url'=>array('index')),
	array('label'=>'Create SystemAdminBasicInfo', 'url'=>array('create')),
	array('label'=>'Update SystemAdminBasicInfo', 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>'Delete SystemAdminBasicInfo', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>'Manage SystemAdminBasicInfo', 'url'=>array('admin')),
);
?>

<h1>View SystemAdminBasicInfo #<?php echo $model->id; ?></h1>

<?php  
//显示数据表格的widget
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'system_admin_id',
		'personal_info_id',
	),
)); ?>
