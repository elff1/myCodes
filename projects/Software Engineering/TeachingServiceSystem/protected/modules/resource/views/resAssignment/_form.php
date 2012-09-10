<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'res-assignment-form',
	'enableAjaxValidation'=>false,
    'htmlOptions'=>array('enctype'=>'multipart/form-data'),
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

    <?php echo $form->errorSummary($model); ?>
    <?php echo $form->errorSummary($res_model); ?>

<!--	<div class="row"> -->
		<?php //echo $form->labelEx($model,'teachingclass_id'); ?>
		<?php //echo $form->textField($model,'teachingclass_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php //echo $form->error($model,'teachingclass_id'); ?>
<!--	</div> -->

<!--	<div class="row"> -->
		<?php //echo $form->labelEx($model,'resource_id'); ?>
		<?php //echo $form->textField($model,'resource_id',array('size'=>11,'maxlength'=>11)); ?>
		<?php //echo $form->error($model,'resource_id'); ?>
<!--	</div> -->

	<div class="row">
    <!-- date picker -->
		<?php echo $form->labelEx($model,'dead_line'); ?>
		<?php //echo $form->textField($model,'dead_line'); ?>
        <?php $this->widget('zii.widgets.jui.CJuiDatePicker', array(
            'attribute' => 'dead_line',
            'model' => $model,
            'options' => array(
                'dateFormat' => 'yy-mm-dd',
            ),
        ));
        ?>
        <?php echo $form->error($model,'dead_line'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'is_published'); ?>
        <?php //echo $form->textField($model,'is_published'); ?>
        <?php echo $form->checkBox($model, 'is_published'); ?>
		<?php echo $form->error($model,'is_published'); ?>
	</div>

<!--	<div class="row"> -->
		<?php //echo $form->labelEx($model,'teacher_id'); ?>
		<?php //echo $form->textField($model,'teacher_id'); ?>
		<?php //echo $form->error($model,'teacher_id'); ?>
<!--	</div> -->

	<div class="row">
		<?php //echo $form->labelEx($model,'publish_time'); ?>
		<?php //echo $form->textField($model,'publish_time'); ?>
		<?php //echo $form->error($model,'publish_time'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'requirement'); ?>
        <?php //echo $form->textArea($model,'requirement',array('size'=>60,'maxlength'=>2048)); ?>
        <?php $this->widget('ext.editMe.ExtEditMe', array(
                'model' => $model,
                'attribute' => 'requirement',
            ));
        ?>
		<?php echo $form->error($model,'requirement'); ?>
	</div>

    <div class="row">
<?php
        echo $form->labelEx($res_model, 'path'); 
        echo $form->fileField($res_model, 'path', '');
        echo $form->error($res_model, 'path');
 ?>
    </div>

    <div class="row">
        <?php echo $form->labelEx($res_model, 'display_name'); ?>
        <?php echo $form->textField($res_model, 'display_name',
        array('size'=>60, 'maxlength'=>255)); ?>
        <?php echo $form->error($res_model, 'display_name'); ?>
    </div>

    <div class="row">
        <?php echo $form->labelEx($res_model, 'description'); ?>
        <?php echo $form->textArea($res_model, 'description', array(
        'size'=>60, 'maxlength'=>2048)); ?>
        <?php echo $form->error($res_model, 'description'); ?>
    </div>
    
	<div class="row buttons">
        <?php echo CHtml::submitButton(
    $model->isNewRecord || $res_model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->
