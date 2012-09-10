<?php
//顶部导航栏
$this->breadcrumbs=array(
	'Student Basic Infos'=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);

//右侧菜单栏
$this->menu=array(
	array('label'=>'List StudentBasicInfo', 'url'=>array('index')),
	array('label'=>'Create StudentBasicInfo', 'url'=>array('create')),
	array('label'=>'View StudentBasicInfo', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage StudentBasicInfo', 'url'=>array('admin')),
);
?>

<h1>Update StudentBasicInfo <?php echo $model->id; ?></h1>
<!--从_form.php加载并显示数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model, 'personalInfoModel'=>$personalInfoModel)); ?>
