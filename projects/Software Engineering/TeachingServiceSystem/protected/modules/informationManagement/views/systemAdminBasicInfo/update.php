<?php
//顶部导航栏
$this->breadcrumbs=array(
	'System Admin Basic Infos'=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);

//右侧菜单栏
$this->menu=array(
	array('label'=>'List SystemAdminBasicInfo', 'url'=>array('index')),
	array('label'=>'Create SystemAdminBasicInfo', 'url'=>array('create')),
	array('label'=>'View SystemAdminBasicInfo', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage SystemAdminBasicInfo', 'url'=>array('admin')),
);
?>

<h1>Update SystemAdminBasicInfo <?php echo $model->id; ?></h1>
<!--从_form.php加载并显示数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model, 'personalInfoModel'=>$personalInfoModel)); ?>
