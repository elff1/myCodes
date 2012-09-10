<?php
//顶部导航栏
$this->breadcrumbs=array(
	'Programs'=>array('index'),
	$model->name=>array('view','id'=>$model->id),
	'Update',
);

//右侧菜单栏
$this->menu=array(
	array('label'=>'List Program', 'url'=>array('index')),
	array('label'=>'Create Program', 'url'=>array('create')),
	array('label'=>'View Program', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage Program', 'url'=>array('admin')),
);
?>

<h1>Update Program <?php echo $model->id; ?></h1>

<!--从_form.php加载并显示数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>