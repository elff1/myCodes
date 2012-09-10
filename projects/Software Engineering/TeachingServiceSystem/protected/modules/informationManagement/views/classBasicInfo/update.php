<?php
//顶部导航栏
$this->breadcrumbs=array(
	'Class Basic Infos'=>array('index'),
	$model->name=>array('view','id'=>$model->id),
	'Update',
);

//右侧菜单栏
$this->menu=array(
	array('label'=>'List ClassBasicInfo', 'url'=>array('index')),
	array('label'=>'Create ClassBasicInfo', 'url'=>array('create')),
	array('label'=>'View ClassBasicInfo', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage ClassBasicInfo', 'url'=>array('admin')),
);
?>

<h1>Update ClassBasicInfo <?php echo $model->id; ?></h1>

<!--从_form.php加载并显示数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>